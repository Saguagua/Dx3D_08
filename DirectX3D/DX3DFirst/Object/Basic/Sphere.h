#pragma once
class Sphere :public Transform
{
	typedef VertexTextureNormal VertexType;
public:
	Sphere(float Rad, UINT sliceCount, UINT stackCount);
	~Sphere();

	void Render();
	void Update();

	Material* GetMaterial() { return _material; }

private:

private:
	void CreateMesh();

	Mesh* _mesh;
	Material* _material;
	MatrixBuffer* _worldBuffer;

	vector<VertexType> _vertices;
	vector<UINT> _indices;

	float _radius;
	UINT _sliceCount;
	UINT _stackCount;
};

