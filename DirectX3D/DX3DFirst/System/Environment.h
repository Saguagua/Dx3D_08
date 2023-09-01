#pragma once
class Environment:public Singleton<Environment>
{
	friend class Singleton;

private:
	Environment();
	~Environment();

	void CreateViewport();
	void CreatePerspective();

public:
	void SetEnvironment();

	void PostRender();

private:
	MatrixBuffer* _projBuffer;
	LightBuffer* _lightBuffer;

	Vector3 lightDirection = V_DOWN;
};

