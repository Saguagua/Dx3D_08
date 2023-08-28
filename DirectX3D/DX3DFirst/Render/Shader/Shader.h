#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:
	static class VertexShader* GetVS(wstring path);
	static class PixelShader* GetPS(wstring path);

	static void Delete();

	virtual void SetShader() abstract;

protected:
	ID3DBlob* _blob;

	static map<wstring, Shader*> _shaders;
};