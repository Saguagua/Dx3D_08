#pragma once
class StateManager :public Singleton<StateManager>
{
	friend class Singleton;

private:
	StateManager();
	~StateManager();

	void    CreateSamplerState();
	void CreateRasterizerState();

public:
	RasterizerState* GetRS() { return _rasterizerState; }

private:
	   SamplerState*    _samplerState = nullptr;
	RasterizerState* _rasterizerState = nullptr;
};

