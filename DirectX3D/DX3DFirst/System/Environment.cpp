#include "framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewport();
    CreatePerspective();
}

Environment::~Environment()
{
    delete _viewBuffer;
    delete _projBuffer;
}

void Environment::CreateViewport()
{
    D3D11_VIEWPORT viewPort; //화면이 그려질 영역

    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    DC->RSSetViewports(1, &viewPort);
}

void Environment::CreatePerspective()
{
    _viewBuffer = new MatrixBuffer();
    _projBuffer = new MatrixBuffer();

    XMVECTOR eyePos = XMVectorSet(0.0f, 5.0f, -15.0f, +1.0f);
    XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, +1.0f);
    XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, +0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);
    //원근감과 카메라 회전을 위해 사용

    _viewBuffer->SetData(view);

    XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f); //Fov -> field of view (시야각)

    _projBuffer->SetData(proj);
    _viewBuffer->SetVSBuffer(1);
    _projBuffer->SetVSBuffer(2);
}
