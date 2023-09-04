#pragma once

class DiffuseCube :public Transform
{
public:
	DiffuseCube(Vector4 color, Vector3 size);
	~DiffuseCube();

	void Update();
	void Render();

private:
	void CreateVertices(Vector4 color);

	Mesh* _mesh;
	Material* _material;
	MatrixBuffer* _worldBuffer;

	vector<VertexColorNormal> _vertices;
	vector<UINT> _indices;
	Vector3 _size;
};