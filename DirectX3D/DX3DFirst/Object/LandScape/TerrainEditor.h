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

	void SaveHeightMap(wstring file);
	void LoadHeightMap(wstring file);

	void SaveHeightDialog();
	void LoadHeightDialog();

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();
	void CreateCompute();

	void AdjustHeight();

	vector<VertexType> _vertices;
	vector<UINT> _indices;

	Material* _material;
	Mesh* _mesh;

	MatrixBuffer* _worldBuffer;

	UINT  _width = 10;
	UINT _height = 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;

	struct InputDesc
	{
		UINT _index;

		Vector3 v0, v1, v2;
	};

	struct OutputDesc
	{
		int isPicked;
		float u, v;

		float distance;
	};

	StructuredBuffer* _sBuffer;
	RayBuffer* _rayBuffer;
	BrushBuffer* _brushBuffer;

	ComputeShader* _computeShader;

	InputDesc* _input;
	OutputDesc* _output;

	UINT _polygonCount;

	Vector3 _pickedPostion;

	float _adjustValue = 20.0f;

	bool _isRaise = true;
};

