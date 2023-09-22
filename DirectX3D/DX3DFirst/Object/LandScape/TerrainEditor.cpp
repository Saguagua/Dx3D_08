#include "framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor(UINT height, UINT width)
	:_height(height), _width(width)
{
	_material = new Material();
	_material->SetShader(L"TerrainBrush");

	_worldBuffer = new MatrixBuffer();

	_brushBuffer = new BrushBuffer();

	BinaryReader data(L"HeightMap");

	if (data.Succeeded())
	{
		wstring heightPath = data.ReadWString();
		_heightMap = Texture::Load(heightPath);
	}

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);

	_rayBuffer = new RayBuffer();
	_computeShader = Shader::GetCS(L"ComputePicking");

	CreateCompute();

	_sBuffer = new StructuredBuffer(_input, sizeof(InputDesc), _polygonCount, sizeof(OutputDesc), _polygonCount);

	

}

TerrainEditor::~TerrainEditor()
{
	if (_heightMap != nullptr)
	{
		BinaryWriter data(L"HeightMap");

		data.WriteData(_heightMap->GetPath());
	}

	delete _mesh;
	delete _worldBuffer;
	delete _material;

	delete[] _input;
	delete[] _output;

	delete _rayBuffer;
	delete _sBuffer;

	delete _brushBuffer;
}

void TerrainEditor::Update()
{
	Transform::Update();

	_brushBuffer->_data.location = _pickedPostion;

	_brushBuffer->UpdateSubresource();

	if (Picking(&_pickedPostion) && KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
		AdjustHeight();
	if (KEY_PRESS(VK_LSHIFT))
		_isRaise = false;
	else
		_isRaise = true;
}

void TerrainEditor::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	_brushBuffer->SetPSBuffer(10);

	DC->DrawIndexed(_indices.size(), 0, 0);
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(_mousePos);

	_rayBuffer->_data.origin = ray.origin;
	_rayBuffer->_data.direction = ray.direction;
	_rayBuffer->_data.outputSize = _polygonCount;

	_rayBuffer->SetCSBuffer(0);

	_sBuffer->SetSRV();
	_sBuffer->SetUAV();

	_computeShader->SetShader();

	UINT groupCount = ceil(_polygonCount / 1024.0f); //1024 -> 5.0 버전 최대

	DC->Dispatch(groupCount, 1, 1);

	_sBuffer->Copy(_output, sizeof(OutputDesc) * _polygonCount);

	float minDistance = FLT_MAX;

	for (size_t i = 0; i < _polygonCount; i++)
	{
		if (_output[i].isPicked)
		{
			if (minDistance > _output[i].distance)
				minDistance = _output[i].distance;
		}
	}

	if (minDistance != FLT_MAX)
	{
		*position = ray.origin + ray.direction * minDistance;


		return true;
	}

	return false;
}

void TerrainEditor::Debug()
{
	ImGui::Text("PickPos : %.001f, %.001f, %.001f", _pickedPostion.x, _pickedPostion.y, _pickedPostion.z);
	ImGui::ColorEdit3("BrushColor", (float*)&_brushBuffer->_data.color);
	ImGui::SliderFloat("BrushIntensity", &_adjustValue, 1.0f, 50.0f);
	ImGui::SliderFloat("BrushRange", &_brushBuffer->_data.range, 1.0f, 50.0f);

	const char* typeList[] = { "Circle", "Rect" };

	ImGui::Combo("BrushType", &_brushBuffer->_data.type, typeList, 2);

	SaveHeightDialog();
	LoadHeightDialog();
}

void TerrainEditor::SaveHeightMap(wstring file)
{
	file = L"_Texture/" + file;

	UINT size = _width * _height * 4;

	uint8_t* pixels = new uint8_t[size];

	for (UINT i = 0; i < size / 4; i++)
	{
		float y = _vertices[i]._pos.y;

		uint8_t height = (y * 255) / MAP_HEIGHT;

		pixels[4 * i + 0] = height;
		pixels[4 * i + 1] = height;
		pixels[4 * i + 2] = height;
		pixels[4 * i + 3] = 255;
	}

	Image image;

	image.width = _width;
	image.height = _height;
	image.pixels = pixels;
	image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	image.rowPitch = _width * 4;
	image.slicePitch = size;

	SaveToWICFile(image, WIC_FLAGS_FORCE_RGB, GetWICCodec(WIC_CODEC_PNG), file.c_str());
}

void TerrainEditor::LoadHeightMap(wstring file)
{

	_heightMap = Texture::Load(file);

	if (_mesh != nullptr)
		delete _mesh;

	_vertices.clear();
	_indices.clear();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);
}

void TerrainEditor::SaveHeightDialog()
{
	if (ImGui::Button("Save HeightMap"))
	{
		DIALOG->OpenDialog("SaveKey", "Save", ".png", "_Texture/HeightMap/");
	}


	if (DIALOG->Display("SaveKey", 32, {200, 100}))
	{
		if (DIALOG->IsOk())
		{
			string path = DIALOG->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());

			SaveHeightMap(ToWString(path));
		}

		DIALOG->Close();
	}
}

void TerrainEditor::LoadHeightDialog()
{
	if (ImGui::Button("Load HeightMap"))
	{
		DIALOG->OpenDialog("LoadKey", "Load", ".png", "_Texture/HeightMap/");
	}


	if (DIALOG->Display("LoadKey", 32, { 200, 100 }))
	{
		if (DIALOG->IsOk())
		{
			string path = DIALOG->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());

			LoadHeightMap(ToWString(path));
		}

		DIALOG->Close();
	}
}

void TerrainEditor::CreateMesh()
{
	vector<Vector4> colors;


	if (_heightMap != nullptr)
	{
		_width = _heightMap->GetSize().x;
		_height = _heightMap->GetSize().y;

		colors = _heightMap->ReadPixels();
	}

	//Vertices
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexType vertex;

			vertex._pos = Vector3(x, 0, z);

			vertex._uv.x = x / (_width - 1);
			vertex._uv.y = 1 - z / (_height - 1);

			if (colors.size() > 0)
			{
				UINT index = x + z * _width;
				vertex._pos.y = colors[index].x * MAP_HEIGHT;
			}

			_vertices.push_back(vertex);
		}
	}

	//Indices
	for (float z = 0; z < _height - 1; z++)
	{
		for (float x = 0; x < _width - 1; x++)
		{
			_indices.push_back(x + 0 + _width * (z + 1)); //7
			_indices.push_back(x + 1 + _width * (z + 1)); //8
			_indices.push_back(x + 0 + _width * (z + 0)); //0

			_indices.push_back(x + 0 + _width * (z + 0)); //0
			_indices.push_back(x + 1 + _width * (z + 1)); //8
			_indices.push_back(x + 1 + _width * (z + 0)); //1
		}
	}
}

void TerrainEditor::CreateNormal()
{
	for (VertexType& vertex : _vertices)
		vertex._normal = Vector3();


	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0]._pos;
		Vector3 p1 = _vertices[index1]._pos;
		Vector3 p2 = _vertices[index2]._pos;

		Vector3 v01 = p1 - p0;
		Vector3 v02 = p2 - p0;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		_vertices[index0]._normal += normal;
		_vertices[index1]._normal += normal;
		_vertices[index2]._normal += normal;
	}
}

void TerrainEditor::CreateTangent()
{
	for (VertexType& vertex : _vertices)
		vertex._tangent = Vector3();

	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0]._pos;
		Vector3 p1 = _vertices[index1]._pos;
		Vector3 p2 = _vertices[index2]._pos;


		Vector2 uv0 = _vertices[index0]._uv;
		Vector2 uv1 = _vertices[index1]._uv;
		Vector2 uv2 = _vertices[index2]._uv;

		Vector3 e01 = p1 - p0;
		Vector3 e02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		float D = 1.0f / (u1 * v2 - v1 * u2); //D->Determinant 여기선 역행렬이 있는지 조사

		Vector3 tangent = D * (e01 * v2 - e02 * v1);

		_vertices[index0]._tangent += tangent;
		_vertices[index1]._tangent += tangent;
		_vertices[index2]._tangent += tangent;
	}

	for (VertexType& vertex : _vertices)
	{
		Vector3 T = vertex._tangent;
		Vector3 N = vertex._normal;

		vertex._tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
	}
}

void TerrainEditor::CreateCompute()
{
	_polygonCount = _indices.size() / 3;

	if (_input != nullptr)
		delete[] _input;

	_input = new InputDesc[_polygonCount];

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i]._index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0]._pos;
		_input[i].v1 = _vertices[index1]._pos;
		_input[i].v2 = _vertices[index2]._pos;
	}

	if (_output != nullptr)
		delete[] _output;

	_output = new OutputDesc[_polygonCount];
}

void TerrainEditor::AdjustHeight()
{
	switch (_brushBuffer->_data.type)
	{
	case 0:
	{
		for (VertexType& vertex : _vertices)
		{
			Vector3 p1 = Vector3(vertex._pos.x, 0.0f, vertex._pos.z);
			Vector3 p2 = Vector3(_pickedPostion.x, 0.0f, _pickedPostion.z);
			
			float distance = (p1 - p2).Length();
			
			float value = _adjustValue * max(0, cos(XM_PIDIV2 * distance / _brushBuffer->_data.range));

			if (distance <= _brushBuffer->_data.range)
			{
				//vertex._pos.y += value * Time::Delta();

				if (_isRaise)
					vertex._pos.y += value * Time::Delta();
				else
					vertex._pos.y -= value * Time::Delta();

				if (vertex._pos.y > MAP_HEIGHT)
					vertex._pos.y = MAP_HEIGHT;

				if (vertex._pos.y < 0)
					vertex._pos.y = 0;
			}
			
		}

		break;
	}
	case 1:
	{
		for (VertexType& vertex : _vertices)
		{
			Vector3 p1 = Vector3(vertex._pos.x, 0.0f, vertex._pos.z);
			Vector3 p2 = Vector3(_pickedPostion.x, 0.0f, _pickedPostion.z);

			Vector3 distance = (p1 - p2);

			if (abs(distance.x) <= _brushBuffer->_data.range &&
				abs(distance.z) <= _brushBuffer->_data.range)
			{
				vertex._pos.y += _adjustValue * Time::Delta();

				if (vertex._pos.y > MAP_HEIGHT)
					vertex._pos.y = MAP_HEIGHT;
			}

		}

		break;
	}

	default:
		break;
	}

	CreateNormal();
	CreateTangent();

	_mesh->UpdateVertex(_vertices.data(), _vertices.size());

	for (UINT i = 0; i < _polygonCount; i++)
	{
		_input[i]._index = i;

		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		_input[i].v0 = _vertices[index0]._pos;
		_input[i].v1 = _vertices[index1]._pos;
		_input[i].v2 = _vertices[index2]._pos;
	}

	_sBuffer->UpdateInput(_input);

}
