#include "framework.h"
#include "Material.h"

string Material::_ID = "";

Material::Material()
{
    _mBuffer = new MaterialBuffer();

    char path[128];
    GetCurrentDirectoryA(128, path);

    _projDir = path ;
    _projDir += "_Texture/";

    _ID += ".";
}

Material::Material(wstring path)
{
    SetShader(path);

    _mBuffer = new MaterialBuffer();

    char curPath[128];
    GetCurrentDirectoryA(128, curPath);

    _projDir = curPath;
    _projDir += "_Texture/";

    _ID += ".";
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

    if (_normalMap)
        _normalMap->PSSetShaderResoureces(2);

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

void Material::SetNormalMap(wstring file)
{
    _normalMap = Texture::Get(file);

    _mBuffer->_data.hasNormalMap = true;
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

void Material::SelectMap()
{

    if (ImGui::BeginChild(_ID.c_str(), ImVec2(100, 85), true))
    {
        if (ImGui::Button("DiffuseMap"))
            DIALOG->OpenDialog("Diffuse", "Select Diffuse", ".png,.jpg,.dds,.tga", "_Texture");

        if (ImGui::Button("SpecularMap"))
            DIALOG->OpenDialog("Specular", "Select Specular", ".png,.jpg,.dds,.tga", "_Texture");

        if (ImGui::Button("NormalMap"))
            DIALOG->OpenDialog("Normal", "Select Normal", ".png,.jpg,.dds,.tga", "_Texture");

        if (DIALOG->Display("Diffuse") || DIALOG->Display("Specular") || DIALOG->Display("Normal"))
        {
            if (DIALOG->IsOk())
            {
                string path = DIALOG->GetFilePathName();

                path = path.substr(_projDir.size() + 1, path.size());

                if (DIALOG->GetOpenedKey() == "Diffuse")
                    SetDiffuseMap(ToWString(path));

                else if (DIALOG->GetOpenedKey() == "Specular")
                    SetSpecularMap(ToWString(path));

                else if (DIALOG->GetOpenedKey() == "Normal")
                    SetNormalMap(ToWString(path));

            }

            DIALOG->Close();
        }


        ImGui::EndChild();
    }
}
