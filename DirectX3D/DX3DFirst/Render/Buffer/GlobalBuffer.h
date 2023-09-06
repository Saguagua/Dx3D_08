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
		_data.padding = 0.0f;
		_data.ambientLight = Vector4(0.1f, 0.1f, 0.1f, 1.0f); //°£Á¢±¤
	}

	struct Data
	{
		Vector3 direction;
		float padding;
		Vector4 ambientLight;
	} _data;
};

class MaterialBuffer : public ConstBuffer
{
public:
	MaterialBuffer()
		:ConstBuffer(&_data, sizeof(_data))
	{

	}

	struct Data
	{
		Vector4 diffuse  = Vector4(1,1,1,1);
		Vector4 specular = Vector4(1,1,1,1);
		Vector4 ambient  = Vector4(1,1,1,1);

		int hasDiffuseMap = 0;
		int hasSpecularMap = 0;
		int hasNormalMap = 0;

		float shininess = 24.0f;
	} _data;
};

class ViewBuffer : public ConstBuffer
{
public:
	ViewBuffer()
		:ConstBuffer(&_data, sizeof(_data))
	{
		_data.view = XMMatrixIdentity();
		_data.invView = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value, XMMATRIX invView)
	{
		_data.view = XMMatrixTranspose(value);
		_data.invView = XMMatrixTranspose(invView);
	}

private:
	struct Data
	{
		XMMATRIX view;
		XMMATRIX invView;
	} _data;
};
