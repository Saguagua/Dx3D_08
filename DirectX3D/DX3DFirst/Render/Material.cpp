#include "framework.h"
#include "Material.h"

int Material::_ID = 0;

Material::Material()
{
    _mBuffer = new MaterialBuffer();


    //SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
    //SetNormalMap(L"Landscape/FieldStone_NM.tga");
    //SetSpecularMap(L"Landscape/FieldStone_SM.tga");


    char path[128];
    GetCurrentDirectoryA(128, path);

    _projDir = path ;
    _projDir += "_Texture/";

    _ID += 1;
    _label = "Material" + to_string(_ID);

}

Material::Material(wstring path)
{
    _mBuffer = new MaterialBuffer();

    SetShader(path);

    SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
    SetSpecularMap(L"Landscape/FieldStone_SM.tga");
    SetNormalMap(L"Landscape/FieldStone_NM.tga");


    char curPath[128];
    GetCurrentDirectoryA(128, curPath);

    _projDir = curPath;
    _projDir += "_Texture/";

    _ID += 1;
    _label = "Material" + to_string(_ID);

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
    ImGui::InputText("Label", (char*)_label.data(), 128);

    if (_label[0] == '\0')
        _label = "NULL";

    if (ImGui::BeginMenu(_label.c_str())) 
    {

        ImGui::ColorEdit4((_label + " Diffuse").c_str(), (float*)&_mBuffer->_data.diffuse);
        ImGui::ColorEdit4((_label + " Specular").c_str(), (float*)&_mBuffer->_data.specular);
        ImGui::ColorEdit4((_label + " Ambient").c_str(), (float*)&_mBuffer->_data.ambient);

        ImGui::Checkbox((_label + " HasDiffuseMap").c_str(), (bool*)&_mBuffer->_data.hasDiffuseMap);
        ImGui::Checkbox((_label + " HasSpecularMap").c_str(), (bool*)&_mBuffer->_data.hasSpecularMap);
        ImGui::Checkbox((_label + " HasNormalMap").c_str(), (bool*)&_mBuffer->_data.hasNormalMap);

        ImGui::SliderFloat("Shininess", &_mBuffer->_data.shininess, 1.0f, 50.0f);

        SaveDialog();
        LoadDialog();

        ImGui::EndMenu();
    }
    
    SelectMap();

}

void Material::SelectMap()
{

    if (ImGui::BeginMenu(_label.c_str()))
    {
        if (ImGui::Button("DiffuseMap"))
            DIALOG->OpenDialog("Diffuse", "Select Diffuse", ".png,.jpg,.dds,.tga", "_Texture");

        if (ImGui::Button("NormalMap"))
            DIALOG->OpenDialog("Normal", "Select Normal", ".png,.jpg,.dds,.tga", "_Texture");

        if (ImGui::Button("SpecularMap"))
            DIALOG->OpenDialog("Specular", "Select Specular", ".png,.jpg,.dds,.tga", "_Texture");

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

        ImGui::EndMenu();
    }
}

void Material::Save(wstring file)
{
    BinaryWriter data(file);

    data.WriteData(_label);

    if (_vertexShader)
        data.WriteData(_vertexShader->GetPath());
    else
        data.WriteData(L"");

    if (_pixelShader)
        data.WriteData(_pixelShader->GetPath());
    else
        data.WriteData(L"");

    if (_diffuseMap)
        data.WriteData(_diffuseMap->GetPath());
    else
        data.WriteData(L"");

    if (_specularMap)
        data.WriteData(_specularMap->GetPath());
    else
        data.WriteData(L"");

    if (_normalMap)
        data.WriteData(_normalMap->GetPath());
    else
        data.WriteData(L"");

    data.WriteData(_mBuffer->_data.diffuse);
    data.WriteData(_mBuffer->_data.specular);
    data.WriteData(_mBuffer->_data.ambient);
    data.WriteData(_mBuffer->_data.emissive);

    data.WriteData(_mBuffer->_data.shininess);
}

void Material::Load(wstring file)
{
    BinaryReader data(file);

    if (!data.Succeeded())
        return;

    _label = data.ReadString();

    wstring path = data.ReadWString();

    if (path != L"")
        _vertexShader = Shader::GetVS(path);

    path = data.ReadWString();

    if (path != L"")
        _pixelShader = Shader::GetPS(path);

    path = data.ReadWString();

    if (path != L"")
        _diffuseMap = Texture::Get(path);

    path = data.ReadWString();

    if (path != L"")
        _specularMap = Texture::Get(path);

    path = data.ReadWString();

    if (path != L"")
        _normalMap = Texture::Get(path);

    _mBuffer->_data.diffuse = data.ReadVector4();
    _mBuffer->_data.specular = data.ReadVector4();
    _mBuffer->_data.ambient = data.ReadVector4();
    _mBuffer->_data.emissive = data.ReadVector4();

    _mBuffer->_data.shininess = data.ReadFloat();
}

void Material::SaveDialog()
{
    if (ImGui::Button(("Save " + _label).c_str()))
    {
        DIALOG->OpenDialog("Save Material", "Save", ".mat", "_Texture/");
    }


    if (DIALOG->Display("Save Material", 32, { 500, 400 }))
    {
        if (DIALOG->IsOk())
        {
            string path = DIALOG->GetFilePathName();

            path = path.substr(GetTextDataDir().size(), path.length());

            Save(ToWString(path));
        }

        DIALOG->Close();
    }
}

void Material::LoadDialog()
{
    if (ImGui::Button(("Load " + _label).c_str()))
    {
        DIALOG->OpenDialog("Load Material", "Load", ".mat", "_Texture/");
    }


    if (DIALOG->Display("Load Material", 32, { 500, 400 }))
    {
        if (DIALOG->IsOk())
        {
            string path = DIALOG->GetFilePathName();

            path = path.substr(GetTextDataDir().size(), path.length());

            Load(ToWString(path));
        }

        DIALOG->Close();
    }
}
