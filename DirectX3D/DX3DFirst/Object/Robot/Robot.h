#pragma once
class Robot
{
	enum PartIndex
	{
		P_BODY,
		P_NECK,
		P_HEAD,
		P_LEFT_EYE,
		P_RIGHT_EYE,
		P_ANTENNA_BODY,
		P_ANTENNA_HEAD,
		P_LEFT_SHOULDER,
		P_RIGHT_SHOULDER, 
		P_LEFT_UPPER_ARM,
		P_RIGHT_UPPER_ARM,
		P_LEFT_ELBOW,
		P_RIGHT_ELBOW,
		P_LEFT_UNDER_ARM,
		P_RIGHT_UNDER_ARM,
		P_STOMACH,
		P_HIP,
		P_LEFT_HIPJOINT,
		P_RIGHT_HIPJOINT,
		P_LEFT_UPPER_LEG,
		P_RIGHT_UPPER_LEG,
		P_LEFT_KNEE,
		P_RIGHT_KNEE,
		P_LEFT_UNDER_LEG,
		P_RIGHT_UNDER_LEG,
		P_LEFT_FOOT,
		P_RIGHT_FOOT
	};

	enum SlotIndex
	{
		S_NECK_HEAD,
		S_LEFT_SHOULDER,
		S_RIGHT_SHOULDER,
		S_LEFT_ELBOW,
		S_RIGHT_ELBOW,
		S_LEFT_HIPJOINT,
		S_RIGHT_HIPJOINT,
		S_LEFT_KNEE,
		S_RIGHT_KNEE,
		S_LEFT_ANKLE,
		S_RIGHT_ANKLE
	};

public:
	Robot();
	~Robot();

	void Update();
	void Render();

private:
	void Initialize();
	void KeyInput();

	void Walk();

	vector<Transform*> _slots;
	vector<DiffuseCube*> _parts;

	float _speed = 5.0f;
	float _direction1 = -1;
	float _direction2 = -1;
	float _direction3 = -1;

	float _upperMaxAngle = 1.0f;
	float _underMaxAngle = -1.0f;

	float _legSpeed = 5.0f;
	float _underLegSpeed = 5.3f;
	float _fistMaxAngle = 60.0f * 3.141592f / 180.0f;
	float _armMaxAngle = 90.0f;
	float _legMaxAngle = 90.0f * 3.141592f / 180.0f;
	float _timer = 0;
};

