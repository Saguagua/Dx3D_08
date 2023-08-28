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

	vector<VertexTexture> _vertices;
	vector<UINT>		  _indices;

	ID3D11ShaderResourceView*		   _srv = nullptr;
	ID3D11SamplerState*		  _samplerState = nullptr;

	MatrixBuffer* _worldBuffer = nullptr;
};

