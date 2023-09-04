#pragma once
class Cylinder :public Transform
{
public:
	Cylinder(float topRad, float bottomRad, float sliceCount, float height, float stackCount);
	~Cylinder();

	void Render();
	void Update();

private:
	void CreateMesh(float topRad, float bottomRad, float sliceCount, float height, float stackCount);

	Mesh* _mesh;
	Material* _material;
	MatrixBuffer* _worldBuffer;

	vector<VertexColorNormal> _vertices;
	vector<UINT> _indices;
};

