#include "framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
}

StateManager::~StateManager()
{
	delete _samplerState;
}

void StateManager::CreateSamplerState()
{
	_samplerState = new SamplerState();
}
