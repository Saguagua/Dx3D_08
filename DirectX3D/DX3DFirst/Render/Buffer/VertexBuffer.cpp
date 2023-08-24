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
