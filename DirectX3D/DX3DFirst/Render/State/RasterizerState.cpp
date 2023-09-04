#include "framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_desc.CullMode = D3D11_CULL_BACK;
	_desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerState);
}

RasterizerState::~RasterizerState()
{
	_rasterizerState->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(_rasterizerState);
}
