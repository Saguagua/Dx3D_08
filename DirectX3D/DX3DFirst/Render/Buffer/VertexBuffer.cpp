#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    _vertexBuffer->Release();
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetPrimitiveTopology(type); //�������� ������
    //����Ʈ�� ��Ʈ���� ���� 
    // ����Ʈ�� ������ 1���� ����� ��Ʈ���� ������ �̾ ������
    //������(�ٰ���) : �ﰢ������ �̾� �ٿ��� ��ü�� ����� ���
    //�������� ����ϴ� ���� : ������ ȿ����
    // ���� : ��������� �Ͼ��
    DC->IASetVertexBuffers(0, 1, &_vertexBuffer, &_stride, &_offset);
}

void VertexBuffer::UpdateVertex(void* data, UINT count)
{
    /*DC->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

    memcpy(_subResource.pData, _data, _dataSize);

    DC->Unmap(_vertexBuffer, 0);*/

    DC->UpdateSubresource(_vertexBuffer, 0, nullptr, data, _stride, count);
}
