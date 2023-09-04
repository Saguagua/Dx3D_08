#include "framework.h"
#include "Cube.h"

int Cube::_count = 0;

Cube::Cube(Vector4 color, Vector3 size)
    :_size(size)
{
    _material = new Material(L"ColorDiffuse");

    CreateMesh(color);
    CreateNormal();

    _mesh = new Mesh(_vertices, _indices);

    _worldBuffer = new MatrixBuffer();
    _count++;
    _label = "Cube" + to_string(_count);
}

Cube::~Cube()
{
    delete _mesh;
    delete _material;
    delete _worldBuffer;
}

void Cube::Update()
{
    Transform::Update();

    _worldBuffer->SetData(_world);
    _worldBuffer->UpdateSubresource();
}

void Cube::Render()
{
    _material->SetMaterial();
    _mesh->SetMesh();

    _worldBuffer->SetVSBuffer(0);

    DC->DrawIndexed(_indices.size(), 0, 0);
}

void Cube::CreateMesh(Vector4 color)
{
    Vector3 halfSize = _size * 0.5f;
    _vertices =
    {
        VertexType(color,{ -halfSize.x, +halfSize.y, -halfSize.z}, Vector3()),
        VertexType(color,{ +halfSize.x, +halfSize.y, -halfSize.z}, Vector3()),
        VertexType(color,{ -halfSize.x, -halfSize.y, -halfSize.z}, Vector3()),
        VertexType(color,{ +halfSize.x, -halfSize.y, -halfSize.z}, Vector3()),
        VertexType(color,{ -halfSize.x, +halfSize.y, +halfSize.z}, Vector3()),

        VertexType(color,{ +halfSize.x, +halfSize.y, +halfSize.z}, Vector3()),
        VertexType(color,{ -halfSize.x, -halfSize.y, +halfSize.z}, Vector3()),
        VertexType(color,{ +halfSize.x, -halfSize.y, +halfSize.z}, Vector3())
    };


    _indices =
    {
        //F
        0,1,2,
        2,1,3,
        //R
        1,5,3,
        3,5,7,
        //T
        0,4,1,
        1,4,5,
        //L
        4,0,6,
        6,0,2,
        //Ba
        5,4,7,
        7,4,6,
        //Bo
        2,3,6,
        6,3,7
    };

}

void Cube::CreateNormal()
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
