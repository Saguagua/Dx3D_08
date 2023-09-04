#pragma once
class Terrian :public Transform
{
public:
	Terrian(wstring diffusePath, wstring heightPath);
	~Terrian();

	void Render();

private:
	void CreateMesh();
	void CreateNormal();

	vector<VertexTextureNormal> _vertices;
	vector<UINT> _indices;

	Material* _material;
	Mesh* _mesh;

	MatrixBuffer* _worldBuffer;

	UINT  _width = 10;
	UINT _height = 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};

