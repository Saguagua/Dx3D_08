#pragma once
class Camera :public Singleton<Camera>
{
private:
	friend class Singleton;
	Camera();
	~Camera();
	
public:
	void Update();
	void PostRender();

	Transform* _transform;
private:
	void   FreeMode();
	void TargetMode();

	void SetView();

private:

	float _moveSpeed = 20.0f;
	float _rotSpeed = 5.0f;

	MatrixBuffer* _viewBuffer;
	Matrix		  _viewMatrix;

	Vector3 _oldPos;
};

