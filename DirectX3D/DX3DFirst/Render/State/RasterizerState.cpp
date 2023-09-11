#include "framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_desc.CullMode = D3D11_CULL_BACK;
	_desc.FillMode = D3D11_FILL_WIREFRAME;

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

void RasterizerState::ChangeState(D3D11_FILL_MODE mode)
{
	if (_rasterizerState != nullptr)
		_rasterizerState->Release();

	_desc.FillMode = mode;

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerState);
	DC->RSSetState(_rasterizerState);
}