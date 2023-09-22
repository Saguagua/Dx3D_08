#pragma once
class ConstBuffer
{
public:
	ConstBuffer(void* data, UINT dataSize);
	virtual ~ConstBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);

	void UpdateSubresource();

private:
	ID3D11Buffer* _constBuffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _dataSize;
};

