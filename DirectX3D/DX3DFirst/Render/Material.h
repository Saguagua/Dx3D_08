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

	MaterialBuffer* GetMBuffer() { return _mBuffer; }

	void PostRender();

private:

	//Shader -> Material
	VertexShader* _vertexShader;
	PixelShader* _pixelShader;

	Texture* _diffuseMap = nullptr; //diffuse -> ���ݻ� ���̰�
	Texture* _specularMap = nullptr;

	MaterialBuffer* _mBuffer;
};

