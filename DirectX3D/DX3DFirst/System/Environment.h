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

private:
	MatrixBuffer* _viewBuffer;
	MatrixBuffer* _projBuffer;
};

