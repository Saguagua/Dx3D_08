#include "framework.h"
#include "ConstBuffer.h"

//리소스
// 버퍼
// 텍스처
// 
// 리소스는 디바이스가 생성한다
//

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
    :_data(data), _dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc    = {};
    bufferDesc.ByteWidth            = dataSize;
    bufferDesc.Usage                = D3D11_USAGE_DYNAMIC;
    bufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &_constBuffer);
    //initdata를 넣기에는 실시간으로 바뀌기 때문에 넣지 않는다
}

ConstBuffer::~ConstBuffer()
{
    _constBuffer->Release();
}

void ConstBuffer::SetVSBuffer(UINT slot)
{
    UpdateSubresource();

    DC->VSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::SetPSBuffer(UINT slot)
{
    UpdateSubresource();

    DC->PSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::UpdateSubresource()
{
    //DC->UpdateSubresource(_constBuffer, 0, nullptr, _data, 0, 0); 편하지만 데이터 갱신이 느리다

    DC->Map(_constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

    memcpy(_subResource.pData, _data, _dataSize);
    
    DC->Unmap(_constBuffer, 0);
}
