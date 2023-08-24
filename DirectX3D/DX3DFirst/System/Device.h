#pragma once
class Device: public Singleton<Device>
{
	friend class Singleton;

private:

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	Device();
	~Device();

public:
	void Clear();
	void Present();

	ID3D11Device*			GetDevice()			{ return _device; }
	ID3D11DeviceContext*	GetDeviceContext()	{ return _deviceContext; }

private:
	ID3D11Device*			_device;						// CPU�� �ٷ�� ��ü, ���𰡸� ���� ��
	ID3D11DeviceContext*	_deviceContext;					// GPU�� �ٷ�� ��ü, ���𰡸� �׸� ��

	IDXGISwapChain*			_swapChain;                     //������۸� �����ϴ� ��� �� �ϳ�

	ID3D11RenderTargetView* _renderTargetView;              //view�� ���� ���� GPU ����, ����۸� �����Ѵ�.
	//PIP(picture in picture) ȭ��ȿ� ȭ�� �����ִ� ��
	//�̴ϸ�, ����Ÿ���� ī�޶� 1���� ����. �� 8������ �����ϴ�
	ID3D11DepthStencilView* _depthStencilView;
};

