#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:
	static class VertexShader* GetVS(wstring path);
	static class PixelShader* GetPS(wstring path);
	static class ComputeShader* GetCS(wstring path);

	static void Delete();

	virtual void SetShader() abstract;

	wstring GetPath() { return _path; }

protected:
	ID3DBlob* _blob;

	static map<wstring, Shader*> _shaders;

	wstring _path;
};
