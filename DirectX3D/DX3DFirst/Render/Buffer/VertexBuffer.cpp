#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    _vertexBuffer->Release();
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetPrimitiveTopology(type); //원초적인 연결방식
    //리스트와 스트립의 차이 
    // 리스트는 도형을 1개씩 만들고 스트립은 도형을 이어서 만들어낸다
    //폴리곤(다각형) : 삼각형들을 이어 붙여서 물체를 만드는 기법
    //폴리곤을 사용하는 이유 : 연산의 효율성
    // 단점 : 계단현상이 일어난다
    DC->IASetVertexBuffers(0, 1, &_vertexBuffer, &_stride, &_offset);
}

void VertexBuffer::UpdateVertex(void* data, UINT count)
{
    /*DC->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

    memcpy(_subResource.pData, _data, _dataSize);

    DC->Unmap(_vertexBuffer, 0);*/

    DC->UpdateSubresource(_vertexBuffer, 0, nullptr, data, _stride, count);
}
