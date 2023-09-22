#include "framework.h"
#include "Mesh.h"


Mesh::~Mesh()
{
	delete _vertexBuffer;
	delete _indexBuffer;
}

void Mesh::SetMesh(D3D11_PRIMITIVE_TOPOLOGY type)
{
	_vertexBuffer->IASetBuffer(type);
	_indexBuffer->IASetBuffer();
}

void Mesh::UpdateVertex(void* data, UINT count)
{
	_vertexBuffer->UpdateVertex(data, count);
}
