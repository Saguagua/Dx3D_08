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

	assert(PathFileExists(path.c_str()));
	
	if (_shaders.count(path) > 0)
		return (VertexShader*)_shaders[path];
	//static cast, dynamic cast
	//static은 강제 dynamic은 안되면 nullptr 반환

	_shaders[path] = new VertexShader(path);

	return (VertexShader*)_shaders[path];
}

PixelShader* Shader::GetPS(wstring path)
{
	path = L"_Shader/Pixel" + path + L".hlsl";

	assert(PathFileExists(path.c_str()));

	if (_shaders.count(path) > 0)
		return (PixelShader*)_shaders[path];

	_shaders[path] = new PixelShader(path);

	return (PixelShader*)_shaders[path];
}

ComputeShader* Shader::GetCS(wstring path)
{
	path = L"_Shader/" + path + L".hlsl";

	assert(PathFileExists(path.c_str()));

	if (_shaders.count(path) > 0)
		return (ComputeShader*)_shaders[path];

	_shaders[path] = new ComputeShader(path);

	return (ComputeShader*)_shaders[path];
}

void Shader::Delete()
{
	for (pair<wstring, Shader*> shader : _shaders)
		delete shader.second;

	_shaders.clear();
}