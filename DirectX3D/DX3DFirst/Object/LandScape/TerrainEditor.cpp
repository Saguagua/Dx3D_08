#include "framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor(UINT height, UINT width)
	:_height(height), _width(width)
{
	_material = new Material();
	_material->SetShader(L"NormalMapping");

	_worldBuffer = new MatrixBuffer();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);
}

TerrainEditor::~TerrainEditor()
{
	delete _worldBuffer;
	delete _mesh;
	delete _material;
}

void TerrainEditor::Update()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void TerrainEditor::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(_mousePos);

	for (UINT z = 0; z < _height - 1; z++)
	{
		for (UINT x = 0; x < _width - 1; x++)
		{
			UINT index[4];
			index[0] = (x + 0) + _width * (z + 0);
			index[1] = (x + 1) + _width * (z + 0);
			index[2] = (x + 0) + _width * (z + 1);
			index[3] = (x + 1) + _width * (z + 1);

			Vector3 pos[4];

			for (UINT i = 0; i < 4; i++)
			{
				pos[i] = _vertices[index[i]]._pos;
			}

			float distance = 0.0f;

			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[0], pos[1], pos[2], distance))
			{
				*position = ray.origin + ray.direction * distance;

				return true;
			}
			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[2], pos[1], pos[3], distance))
			{
				*position = ray.origin + ray.direction * distance;

				return true;
			}
		}
	}

	return false;
}

void TerrainEditor::Debug()
{
}

void TerrainEditor::CreateMesh()
{
	//Vertices
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexType vertex;

			vertex._pos = Vector3(x, 0, z);

			vertex._uv.x = x / (_width - 1);
			vertex._uv.y = 1 - z / (_height - 1);

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
