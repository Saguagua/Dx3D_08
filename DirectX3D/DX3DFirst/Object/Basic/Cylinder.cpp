#include "framework.h"
#include "Cylinder.h"

Cylinder::Cylinder(float topRad, float bottomRad, float sliceCount, float height, float stackCount)
{
	_material = new Material();
	_material->SetShader(L"ColorDiffuse");
	_worldBuffer = new MatrixBuffer();

	CreateMesh(topRad, bottomRad, sliceCount, height, stackCount);

	_mesh = new Mesh(_vertices, _indices);
}

Cylinder::~Cylinder()
{
	delete _worldBuffer;
	delete _material;
	delete _mesh;
}

void Cylinder::Render()
{
	_worldBuffer->SetVSBuffer(0);
	_material->SetMaterial();
	_mesh->SetMesh();

	DC->DrawIndexed(_indices.size(),0,0);
}

void Cylinder::Update()
{
	Transform::Update();
	_worldBuffer->SetData(_world);
	_worldBuffer->UpdateSubresource();
}

void Cylinder::CreateMesh(float topRad, float bottomRad, float sliceCount, float height, float stackCount)
{
	float ringCount = stackCount + 1;
	float radStep = (topRad - bottomRad) / stackCount;
	float stackHeight = height / stackCount;


	for (int i = 0; i < ringCount; i++)
	{
		float y = height * -0.5f + stackHeight * i;
		float curRad = radStep * i + bottomRad;
		float theta = 2 * XM_PI / sliceCount;

		for (int j = 0; j <= sliceCount; j++)
		{
			VertexColorNormal vertex;
			vertex._pos.x = curRad * cosf(theta * j);
			vertex._pos.z = curRad * sinf(theta * j);
			vertex._pos.y = y;
			vertex._color = Vector4(0, 1, 1, 1);
			_vertices.push_back(vertex);
		}
	}

	int ringVertexCount = sliceCount + 1;

	for (int i = 0; i < stackCount; i++)
	{
		for (int j = 0; j < sliceCount; j++)
		{
			_indices.push_back((i + 0) * ringVertexCount + (j + 0));
			_indices.push_back((i + 1) * ringVertexCount + (j + 0));
			_indices.push_back((i + 1) * ringVertexCount + (j + 1));

			_indices.push_back((i + 0) * ringVertexCount + (j + 0));
			_indices.push_back((i + 1) * ringVertexCount + (j + 1));
			_indices.push_back((i + 0) * ringVertexCount + (j + 1));
		}
	}

	VertexColorNormal vertexBottom;
	vertexBottom._color = Vector4(0, 1, 1, 1);
	vertexBottom._pos = Vector3(0.0f, height * -0.5f, 0.0f);

	_vertices.push_back(vertexBottom);
	int bottomIndex = _vertices.size() - 1;

	for (int i = 0; i < sliceCount; i++)
	{
		_indices.push_back(bottomIndex);
		_indices.push_back(i + 0);
		_indices.push_back(i + 1);
	}

	VertexColorNormal vertexTop;
	vertexTop._color = Vector4(0, 1, 1, 1);
	vertexTop._pos = Vector3(0.0f, height * 0.5f, 0.0f);

	_vertices.push_back(vertexTop);

	int topIndex = _vertices.size() - 1;

	for (int i = _vertices.size() - 3 - sliceCount; i < topIndex - 2; i++)
	{
		_indices.push_back(topIndex);
		_indices.push_back(i + 1);
		_indices.push_back(i + 0);
	}
	
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
