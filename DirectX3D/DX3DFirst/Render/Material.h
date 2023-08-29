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

private:

	//Shader -> Material
	VertexShader* _vertexShader;
	PixelShader* _pixelShader;

	Texture* _diffuseMap = nullptr; //diffuse -> 난반사 깊이감
};

