#pragma once
class Material
{
public:
	Material();
	Material(wstring path);
	~Material();

	void Set_VSShader(wstring path);
	void Set_PSShader(wstring path);

	void SetShader(wstring path);

	void SetMaterial();

	void SetDiffuseMap(wstring file);
	void SetSpecularMap(wstring file);
	void SetNormalMap(wstring file);

	MaterialBuffer* GetMBuffer() { return _mBuffer; }

	void PostRender();

	void SelectMap();

	void Save(wstring file);
	void Load(wstring file);

	void SaveDialog();
	void LoadDialog();

	void SetLabel(string label) { _label = label; }

	string GetLabel() { return _label; }

private:

	//Shader -> Material
	VertexShader* _vertexShader;
	PixelShader* _pixelShader;

	Texture* _diffuseMap = nullptr; //diffuse -> 난반사 깊이감
	Texture* _specularMap = nullptr;
	Texture* _normalMap = nullptr;

	MaterialBuffer* _mBuffer;

	string _projDir;

	static int _ID;
	string _label = "";
};

