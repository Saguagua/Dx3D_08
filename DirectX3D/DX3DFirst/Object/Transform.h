#pragma once
class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return _world; }

	void SetParent(Transform* other) { _parent = other; }

	Vector3	  Forward() { return _forward; }
	Vector3	 Backward() { return _forward * -1; }
	Vector3		Right() { return _right; }
	Vector3      Left() { return _right * -1; }
	Vector3		   Up() { return _up; }
	Vector3		 Down() { return _up * -1; }

	void Debug();
	void SetLabel(string label) { this->_label = label; }
public:
	Vector3 _scale = {1.0f, 1.0f, 1.0f};
	Vector3 _rotation = {0.0f, 0.0f, 0.0f};
	Vector3 _translation = {0.0f, 0.0f, 0.0f};

protected:
	Matrix _world;

	string _label = "";
	
	Vector3 _pivot = {};

	Transform* _parent = nullptr;

	Vector3 _globalScale;
	Vector3 _globalRotation;
	Vector3 _globalTranslation;

	Vector3 _right, _up, _forward;
};

