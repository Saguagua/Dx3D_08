#include "framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;

	_vertices =
	{
		{Vector3(L, T, 0.0f), Vector2(0.0f, 0.0f)},
		{Vector3(R, T, 0.0f), Vector2(1.0f, 0.0f)},
		{Vector3(L, B, 0.0f), Vector2(0.0f, 1.0f)},
		{Vector3(R, B, 0.0f), Vector2(1.0f, 1.0f)},
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"Texture");
	_material->SetDiffuseMap(L"Landscape/Box.png");

	_worldBuffer = new MatrixBuffer();
}

Quad::~Quad()
{
	delete _mesh;
	delete _worldBuffer;
}

void Quad::Render()
{
	_worldBuffer->SetData(Transform::_world);
	_worldBuffer->SetVSBuffer(0);

	_material->SetMaterial();
	_mesh->SetMesh();


	DC->DrawIndexed(_indices.size(), 0, 0);
}