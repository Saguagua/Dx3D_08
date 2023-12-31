#pragma once
class Cube :public Transform
{
	typedef VertexColorNormal VertexType;

public:
	Cube(Vector4 color, Vector3 size = Vector3(2,2,2));
	~Cube();

	void Update();
	void Render();

	void CreateMesh(Vector4 color);
	void CreateNormal();

private:
	Material* _material;
	//Vertex/Index -> Mesh
	Mesh* _mesh;

	MatrixBuffer* _worldBuffer;

	vector<VertexType> _vertices;
	vector<UINT> _indices;

	static int _count;

	Vector3 _size = {2,2,2};
};

