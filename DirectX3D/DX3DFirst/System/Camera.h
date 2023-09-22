#pragma once
struct Ray
{
	Vector3 origin;
	Vector3 direction;
};


class Camera :public Singleton<Camera>
{
private:
	friend class Singleton;
	Camera();
	~Camera();
	
public:
	void Update();
	void PostRender();

	Ray ScreenPointToRay(Vector3 screenPos);

	Transform* _transform;
private:
	void   FreeMode();
	void TargetMode();

	void SetView();

	void Save();
	void Load();

private:

	float _moveSpeed = 20.0f;
	float _rotSpeed = 5.0f;

	ViewBuffer* _viewBuffer;
	Matrix		  _viewMatrix;

	Vector3 _oldPos;
};

