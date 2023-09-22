#include "framework.h"
#include "ComputeShader.h"

ComputeShader::ComputeShader(wstring path)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


    D3DCompileFromFile
    (
        path.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "cs_5_0",
        flags,
        0,
        &_blob, //파일 정보를 불러와서 저장하는 객체
        nullptr
    );

    DEVICE->CreateComputeShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, &_shader);

}

ComputeShader::~ComputeShader()
{
    _shader->Release();
}

void ComputeShader::SetShader()
{
    DC->CSSetShader(_shader, nullptr, 0);
}
