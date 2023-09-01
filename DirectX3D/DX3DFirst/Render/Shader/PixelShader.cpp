#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring path)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
   

    D3DCompileFromFile
    (
        path.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ps_5_0",
        flags,
        0,
        &_blob, //���� ������ �ҷ��ͼ� �����ϴ� ��ü
        nullptr
    );

    DEVICE->CreatePixelShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_pixelShader);

}

PixelShader::~PixelShader()
{
    _pixelShader->Release();
}

void PixelShader::SetShader()
{

    DC->PSSetShader(_pixelShader, nullptr, 0);
}
