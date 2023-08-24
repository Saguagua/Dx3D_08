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
	ID3D11Device*			_device;						// CPU를 다루는 객체, 무언가를 만들 때
	ID3D11DeviceContext*	_deviceContext;					// GPU를 다루는 객체, 무언가를 그릴 때

	IDXGISwapChain*			_swapChain;                     //더블버퍼를 구현하는 방식 중 하나

	ID3D11RenderTargetView* _renderTargetView;              //view가 들어가면 전부 GPU 관련, 백버퍼를 관리한다.
	//PIP(picture in picture) 화면안에 화면 보여주는 것
	//미니맵, 렌더타겟은 카메라 1개와 같다. 총 8개까지 가능하다
	ID3D11DepthStencilView* _depthStencilView;
};

