#include "framework.h"
#include "Cube.h"

int Cube::_count = 0;

Cube::Cube(Vector4 color, Vector3 size)
    :_size(size)
{
    _material = new Material(L"Tutorial");

    CreateMesh(color);

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
        VertexColor(color,{ -halfSize.x, +halfSize.y, -halfSize.z}),
        VertexColor(color,{ +halfSize.x, +halfSize.y, -halfSize.z}),
        VertexColor(color,{ -halfSize.x, -halfSize.y, -halfSize.z}),
        VertexColor(color,{ +halfSize.x, -halfSize.y, -halfSize.z}),

        VertexColor(color,{ -halfSize.x, +halfSize.y, +halfSize.z}),
        VertexColor(color,{ +halfSize.x, +halfSize.y, +halfSize.z}),
        VertexColor(color,{ -halfSize.x, -halfSize.y, +halfSize.z}),
        VertexColor(color,{ +halfSize.x, -halfSize.y, +halfSize.z})
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

    _mesh = new Mesh(_vertices, _indices);
}
