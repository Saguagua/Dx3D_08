#include "framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
}

StateManager::~StateManager()
{
	delete _samplerState;
	delete _rasterizerState;
}

void StateManager::CreateSamplerState()
{
	_samplerState = new SamplerState();
}

void StateManager::CreateRasterizerState()
{
	_rasterizerState = new RasterizerState();
	_rasterizerState->SetState();
}
