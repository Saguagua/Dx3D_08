#include "framework.h"
#include "Device.h"

Device::Device()
{
    CreateDeviceAndSwapChain();
    CreateBackBuffer();
}

Device::~Device()
{
    _device->Release();
    _deviceContext->Release();
    _swapChain->Release();
    _renderTargetView->Release();
    _depthStencilView->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //RGBA 8비트 4개, unorm = unsigned normal = 0 ~ 1

    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = _hWnd;

    //sampling : 표본화. 확대, 축소 연산의 값을 미리 계산해 도움을 준다. 계단현상을 없애준다.
    swapChainDesc.SampleDesc.Count = 1;     //주변 픽셀 몇 개
    swapChainDesc.SampleDesc.Quality = 0;   //범위는 얼마나
    //AA : 안티엘리어싱 
    //엘리어싱 : 계단현상

    swapChainDesc.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &_swapChain,
        &_device,
        nullptr,
        &_deviceContext
    );
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    //IID 클래스 고유 아이디
    //void* 포인터 변수가 들어올 건데 어떤 타입이 들어올 지 모를 때 사용함. template과 비슷
    _device->CreateRenderTargetView(backBuffer, nullptr, &_renderTargetView);

    backBuffer->Release();

    //depthStancilView : 반사 같은 걸 다룬다
    ID3D11Texture2D* depthBuffer;

    D3D11_TEXTURE2D_DESC depthDesc;

    depthDesc.Width            = WIN_WIDTH;
    depthDesc.Height           = WIN_HEIGHT;
    depthDesc.MipLevels        = 1;//확대 축소
    depthDesc.ArraySize        = 1;
    depthDesc.Format           = DXGI_FORMAT_D24_UNORM_S8_UINT;//중요 32비트를 어떻게 나눠서 사용하는가 X는 Undefined
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage            = D3D11_USAGE_DEFAULT;           //중요
    depthDesc.BindFlags        = D3D11_BIND_DEPTH_STENCIL;      //중요
    depthDesc.CPUAccessFlags   = 0;
    depthDesc.MiscFlags        = 0;

    _device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

    dsvDesc.Format = depthDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    _device->CreateDepthStencilView(depthBuffer, &dsvDesc, &_depthStencilView);

    depthBuffer->Release();

    _deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView); //OM : OutPutMerger
}

void Device::Clear()
{
    float clearColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
    _deviceContext->ClearRenderTargetView(_renderTargetView, clearColor);
    _deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Device::Present()
{
    _swapChain->Present(0, 0);  //프리젠트 : 보여주다 백버퍼를 보여준다.
}
