#pragma once
class Quad : public Transform
{
public:
	Quad(Vector2 size = {1.0f,1.0f});
	~Quad();

	void Render();

private:
	Material* _material = nullptr;
	Mesh*		  _mesh	= nullptr;

	vector<VertexTextureNormal> _vertices;
	vector<UINT>		  _indices;

	MatrixBuffer* _worldBuffer = nullptr;
};

