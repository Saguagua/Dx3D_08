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

class LightBuffer : public ConstBuffer
{
public:
	LightBuffer()
		:ConstBuffer(&_data, sizeof(_data))
	{
		_data.direction = V_DOWN;
	}

	void SetData(Vector3 direction)
	{
		_data.direction = direction;
	}

private:
	struct Data
	{
		Vector3 direction;
		float padding;
	} _data;
};