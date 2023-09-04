#pragma once
class Sphere :public Transform
{
public:
	Sphere(float Rad, UINT sliceCount, UINT stackCount);
	~Sphere();

	void Render();
	void Update();

private:
	void CreateMesh(float topRad, UINT sliceCount, UINT stackCount);
	void CreateGeosphere(float radius, UINT numSubdivisions);
	Mesh* _mesh;
	Material* _material;
	MatrixBuffer* _worldBuffer;

	vector<VertexColorNormal> _vertices;
	vector<UINT> _indices;
};

