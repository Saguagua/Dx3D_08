#pragma once


class TerrainEditor :public Transform
{
	typedef VertexTextureNormalTangent VertexType;

public:
	TerrainEditor(UINT height = 100, UINT width = 100);
	~TerrainEditor();

	void Update();
	void Render();

	Material* GetMaterial() { return _material; }

	bool Picking(OUT Vector3* position);

	void Debug();
private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();

	vector<VertexType> _vertices;
	vector<UINT> _indices;

	Material* _material;
	Mesh* _mesh;

	MatrixBuffer* _worldBuffer;

	UINT  _width = 10;
	UINT _height = 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};

