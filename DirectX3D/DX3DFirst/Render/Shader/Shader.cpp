#include "framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::_shaders = {};

Shader::~Shader()
{
	_blob->Release();
}

VertexShader* Shader::GetVS(wstring path)
{
	path = L"_Shader/Vertex" + path + L".hlsl";
	
	if (_shaders.count(path) > 0)
		return (VertexShader*)_shaders[path];
	//static cast, dynamic cast
	//static�� ���� dynamic�� �ȵǸ� nullptr ��ȯ

	_shaders[path] = new VertexShader(path);

	return (VertexShader*)_shaders[path];
}

PixelShader* Shader::GetPS(wstring path)
{
	path = L"_Shader/Pixel" + path + L".hlsl";

	if (_shaders.count(path) > 0)
		return (PixelShader*)_shaders[path];

	_shaders[path] = new PixelShader(path);

	return (PixelShader*)_shaders[path];
}

void Shader::Delete()
{
	for (pair<wstring, Shader*> shader : _shaders)
		delete shader.second;

	_shaders.clear();
}