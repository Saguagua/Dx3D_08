#include "framework.h"
#include "Material.h"

Material::Material()
{
    _vertexShader = Shader::GetVS(L"Tutorial");
    _pixelShader = Shader::GetPS(L"Tutorial");
}

Material::Material(wstring path)
{
    SetShader(path);
}

Material::~Material()
{
}

void Material::Set_VSShader(wstring path)
{
    _vertexShader = Shader::GetVS(path);
}

void Material::Set_PSShader(wstring path)
{
    _pixelShader = Shader::GetPS(path);
}

void Material::SetShader(wstring path)
{
    Set_VSShader(path);
    Set_PSShader(path);
}

void Material::SetMaterial()
{
    _vertexShader->SetShader();
    _pixelShader->SetShader();
}
