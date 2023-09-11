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

    _projectionMatrix = XMMatrixPerspectiveFovLH(
        XM_PIDIV4,
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    ); //Fov -> field of view (시야각)

    _projBuffer->SetData(_projectionMatrix);

    _projBuffer->SetVSBuffer(2);
}

void Environment::SetEnvironment()
{
    _lightBuffer->SetPSBuffer(0);
}

void Environment::PostRender()
{
    ImGui::SliderFloat3("LightDirection", (float*)&_lightBuffer->_data.direction, -1.0f, 1.0f);
    ImGui::ColorEdit4("AmbientLight", (float*)&_lightBuffer->_data.ambientLight);
}