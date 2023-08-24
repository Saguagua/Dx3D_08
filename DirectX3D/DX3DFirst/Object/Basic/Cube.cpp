#include "framework.h"
#include "Cube.h"

int Cube::_count = 0;
Cube::Cube(Vector4 color)
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
    _vertices =
    {
        VertexColor(color,{ -1.0f,  1.0f, -1.0f}),
        VertexColor(color,{  1.0f,  1.0f, -1.0f}),
        VertexColor(color,{ -1.0f, -1.0f, -1.0f}),
        VertexColor(color,{  1.0f, -1.0f, -1.0f}),

        VertexColor(color,{ -1.0f,  1.0f, 1.0f}),
        VertexColor(color,{  1.0f,  1.0f, 1.0f}),
        VertexColor(color,{ -1.0f, -1.0f, 1.0f}),
        VertexColor(color,{  1.0f, -1.0f, 1.0f})
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

void Cube::Debug()
{
    if (ImGui::BeginMenu(_label.c_str()))
    {
        ImGui::DragFloat3("Scale",      (float*)&_scale,        0.01f, 0.01f, 100.0f);
        
        ImGui::SliderAngle("RotationX", &_rotation.x);
        ImGui::SliderAngle("RotationY", &_rotation.y);
        ImGui::SliderAngle("RotationZ", &_rotation.z);

        // 오일러각은 구현하기 쉽지만 짐벌락 현상이 나타나 3D에선 사용할 수 없다
        // 이에 대한 해결방법이 쿼터니언이다

        //ImGui::DragFloat3("Rotation",   (float*)&_rotation,     0.01f, -XM_2PI, XM_2PI);
        ImGui::DragFloat3("Translate",  (float*)&_translation,  0.01f, -WIN_WIDTH, WIN_WIDTH);

        ImGui::EndMenu();
    }
}
