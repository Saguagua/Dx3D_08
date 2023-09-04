#include "framework.h"
#include "Sphere.h"

Sphere::Sphere(float rad, UINT slice, UINT stack)
{
	_material = new Material();
	_material->SetShader(L"ColorDiffuse");
	CreateMesh(rad, slice, stack);
	_mesh = new Mesh(_vertices, _indices);
	_worldBuffer = new MatrixBuffer();
}

Sphere::~Sphere()
{
	delete _material;
	delete _mesh;
	delete _worldBuffer;
}

void Sphere::Render()
{
	_worldBuffer->SetVSBuffer(0);
	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Sphere::Update()
{
	Transform::Update();

	_worldBuffer->SetData(_world);
	_worldBuffer->UpdateSubresource();
}

void Sphere::CreateMesh(float rad, UINT sliceCount, UINT stackCount)
{
    _vertices.clear();
    _indices.clear();

    float phiStep = XM_PI / stackCount;
    float thetaStep = 2.0f * XM_PI / sliceCount;

    VertexColorNormal top;
    top._pos = {0, rad, 0};
    top._color = { 1,0,0,1 };

    VertexColorNormal bottom;
    bottom._pos = { 0, -rad, 0 };
    bottom._color = { 1,0,0,1 };

    _vertices.push_back(top);

    for (UINT i = 1; i <= stackCount - 1; ++i)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; ++j)
        {
            float theta = j * thetaStep;

            VertexColorNormal v;

            v._pos.x = rad * sinf(phi) * cosf(theta);
            v._pos.y = rad * cosf(phi);
            v._pos.z = rad * sinf(phi) * sinf(theta);

            v._color = Vector4(1, 0, 0, 1);

            _vertices.push_back(v);
        }
    }

    _vertices.push_back(bottom);


    for (UINT i = 1; i <= sliceCount; ++i)
    {
        _indices.push_back(0);
        _indices.push_back(i + 1);
        _indices.push_back(i);
    }

    UINT baseIndex = 1;
    UINT ringVertexCount = sliceCount + 1;

    for (UINT i = 0; i < stackCount - 2; ++i)
    {
        for (UINT j = 0; j < sliceCount; ++j)
        {
            _indices.push_back(baseIndex + i * ringVertexCount + j);
            _indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            _indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            
            _indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            _indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            _indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    //
    // Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
    // and connects the bottom pole to the bottom ring.
    //

    // South pole vertex was added last.
    UINT southPoleIndex = (UINT)_vertices.size() - 1;

    // Offset the indices to the index of the first vertex in the last ring.
    baseIndex = southPoleIndex - ringVertexCount;

    for (UINT i = 0; i < sliceCount; ++i)
    {
        _indices.push_back(southPoleIndex);
        _indices.push_back(baseIndex + i);
        _indices.push_back(baseIndex + i + 1);
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