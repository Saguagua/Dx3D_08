#include "framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewport();
    CreatePerspective();
    
    _lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete _lightBuffer;
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
    _projBuffer = new MatrixBuffer();

    XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f); //Fov -> field of view (시야각)

    _projBuffer->SetData(proj);
    _projBuffer->SetVSBuffer(2);
}

void Environment::SetEnvironment()
{
    _lightBuffer->SetVSBuffer(3);
}

void Environment::PostRender()
{
    ImGui::SliderFloat3("LightDirection", (float*)&lightDirection, -1.0f, 1.0f);

    _lightBuffer->SetData(lightDirection);
}
