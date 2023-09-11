#include "framework.h"
#include "Sphere.h"

Sphere::Sphere(float rad, UINT slice, UINT stack)
    :_radius(rad), _sliceCount(slice), _stackCount(stack)
{
	CreateMesh();
    Tangent();
    //slice는 세로 stack은 가로 갯수
	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"NormalMapping");
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

void Sphere::Tangent()
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
