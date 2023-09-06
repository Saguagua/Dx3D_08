#include "framework.h"
#include "Terrian.h"

Terrian::Terrian(wstring diffusePath, wstring heightPath)
{
	_material = new Material();
	_material->SetShader(L"Specular");
	_material->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	_material->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");

	_worldBuffer = new MatrixBuffer();

	_heightMap = Texture::Get(heightPath);

	CreateMesh();
	CreateNormal();

	_mesh = new Mesh(_vertices, _indices);
}

Terrian::~Terrian()
{
	delete _worldBuffer;
	delete _mesh;
	delete _material;
}

void Terrian::Render()
{
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Terrian::CreateMesh()
{
	_height = _heightMap->GetSize().y;
	_width = _heightMap->GetSize().x;

	vector<Vector4> colors = _heightMap->ReadPixels();

	//Vertices
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexTextureNormal vertex;

			vertex._pos = Vector3(x, 0, z);

			vertex._uv.x = x / (_width - 1);
			vertex._uv.y = 1 - z / (_height - 1);

			//HeightMap
			UINT index = x + z * _width;
			vertex._pos.y = colors[index].x * MAP_HEIGHT;

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

void Terrian::CreateNormal()
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
