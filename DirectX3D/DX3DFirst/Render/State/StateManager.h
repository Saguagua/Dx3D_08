#pragma once
class StateManager :public Singleton<StateManager>
{
	friend class Singleton;

private:
	StateManager();
	~StateManager();

	void    CreateSamplerState();
	void CreateRasterizerState();

	   SamplerState*    _samplerState = nullptr;
	RasterizerState* _rasterizerState = nullptr;
};

