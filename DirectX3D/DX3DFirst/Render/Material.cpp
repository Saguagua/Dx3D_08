#include "framework.h"
#include "Material.h"

Material::Material()
{
    _mBuffer = new MaterialBuffer();
}

Material::Material(wstring path)
{
    SetShader(path);

    _mBuffer = new MaterialBuffer();
}

Material::~Material()
{
    delete _mBuffer;
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

    if (_diffuseMap)
        _diffuseMap->PSSetShaderResoureces(0);

    if (_specularMap)
        _specularMap->PSSetShaderResoureces(1);

    _mBuffer->SetPSBuffer(1);
}

void Material::SetDiffuseMap(wstring file)
{
    _diffuseMap = Texture::Get(file);

    _mBuffer->_data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
    _specularMap = Texture::Get(file);

    _mBuffer->_data.hasSpecularMap = true;
}

void Material::PostRender()
{
    ImGui::ColorEdit4("Diffuse", (float*)&_mBuffer->_data.diffuse);
    ImGui::ColorEdit4("Specular", (float*)&_mBuffer->_data.specular);
    ImGui::ColorEdit4("Ambient", (float*)&_mBuffer->_data.ambient);

    ImGui::Checkbox("HasDiffuseMap", (bool*)&_mBuffer->_data.hasDiffuseMap);
    ImGui::Checkbox("HasSpecularMap", (bool*)&_mBuffer->_data.hasSpecularMap);
    ImGui::Checkbox("HasNormalMap", (bool*)&_mBuffer->_data.hasNormalMap);

    ImGui::SliderFloat("Shininess", &_mBuffer->_data.shininess, 1.0f, 50.0f);
}
