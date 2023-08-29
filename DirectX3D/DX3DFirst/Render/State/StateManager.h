#pragma once
class StateManager :public Singleton<StateManager>
{
	friend class Singleton;

private:
	StateManager();
	~StateManager();

	void CreateSamplerState();

	SamplerState* _samplerState = nullptr;
};

