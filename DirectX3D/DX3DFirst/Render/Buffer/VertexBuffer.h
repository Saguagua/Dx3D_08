#pragma once

class VertexBuffer
{
public:
	template<typename T>
	VertexBuffer(vector<T>& vertices);
	~VertexBuffer();

	void IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
private:
	ID3D11Buffer* _vertexBuffer;

    UINT _stride = 0;

    UINT _offset = 0;
};

template<typename T>
inline VertexBuffer::VertexBuffer(vector<T>& vertices)
{
    _stride = sizeof(T);
    _offset = 0;

    D3D11_BUFFER_DESC bufferDesc    = {};
    bufferDesc.ByteWidth            = _stride * vertices.size();
    bufferDesc.Usage                = D3D11_USAGE_DEFAULT; //�߿��� ���� ������ �ٲ� �� �������� �ٲ�� cpu�� ���� ��������(�߰� ����)
    bufferDesc.BindFlags            = D3D11_BIND_VERTEX_BUFFER; //
    bufferDesc.CPUAccessFlags       = 0;
    bufferDesc.MiscFlags            = 0;
    bufferDesc.StructureByteStride  = 0;

    D3D11_SUBRESOURCE_DATA data;

    data.pSysMem = vertices.data(); //&vertices[0] -> ��� ������ ��� ����

    DEVICE->CreateBuffer(&bufferDesc, &data, &_vertexBuffer);
    
}
