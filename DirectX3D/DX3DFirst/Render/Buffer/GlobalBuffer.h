#pragma once
class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer()
		:ConstBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value)
	{
		_data.matrix = XMMatrixTranspose(value);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	} _data;
};