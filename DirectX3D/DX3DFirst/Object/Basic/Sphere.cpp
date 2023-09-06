#include "framework.h"
#include "Sphere.h"

Sphere::Sphere(float rad, UINT slice, UINT stack)
    :_radius(rad), _sliceCount(slice), _stackCount(stack)
{
	CreateMesh();
    //slice는 세로 stack은 가로 갯수
	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"Specular");
	_worldBuffer = new MatrixBuffer();
}

Sphere::~Sphere()
{
	delete _mesh;
	delete _material;
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

void Sphere::CreateMesh()
{
    _vertices.clear();
    _indices.clear();

    float phiStep = XM_PI / _stackCount;
    float thetaStep = XM_2PI / _sliceCount;


    for (UINT i = 0; i <= _stackCount; ++i)
    {
        float phi = i * phiStep; //세로 

        for (UINT j = 0; j < _sliceCount + 1; ++j)
        {
            float theta = j * thetaStep; //가로

            VertexType v;

            v._pos.x = _radius * sinf(phi) * cosf(theta);
            v._pos.y = _radius * cosf(phi);
            v._pos.z = _radius * sinf(phi) * sinf(theta);

            v._normal = v._pos / _radius;

            v._uv.x = j / (float)_sliceCount;
            v._uv.y = i / (float)_sliceCount;

            _vertices.push_back(v);
        }
    }
   
    for (UINT j = 0; j < _stackCount; j++)
    {
        for (UINT i = 0; i < _sliceCount; i++)
        {
            _indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
            _indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));
            _indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));

            _indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));
            _indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));
            _indices.push_back(i + 1 + (_sliceCount + 1) * (j + 1));
        }
    }

}