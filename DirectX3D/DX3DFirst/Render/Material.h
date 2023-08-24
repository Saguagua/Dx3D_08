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


private:

	//Shader -> Material
	VertexShader* _vertexShader;
	PixelShader* _pixelShader;
};

