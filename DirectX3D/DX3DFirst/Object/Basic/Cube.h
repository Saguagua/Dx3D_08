#pragma once
class Cube :public Transform
{
public:
	Cube(Vector4 color);
	~Cube();

	void Update();
	void Render();

	void CreateMesh(Vector4 color);

	void Debug();
private:
	Material* _material;
	//Vertex/Index -> Mesh
	Mesh* _mesh;

	MatrixBuffer* _worldBuffer;

	vector<VertexColor> _vertices;
	vector<UINT> _indices;

	static int _count;
	string _label = "";
};

