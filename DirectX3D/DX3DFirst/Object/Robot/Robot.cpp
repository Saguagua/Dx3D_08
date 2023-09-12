#include "framework.h"
#include "Robot.h"

Robot::Robot()
{
	Initialize();
}

Robot::~Robot()
{
	for (int i = 0; i < _parts.size(); i++)
	{
		delete _parts[i];
	}

	for (int i = 0; i < _slots.size(); i++)
	{
		delete _slots[i];
	}

	_parts.clear();
	_slots.clear();
}

void Robot::Update()
{
	for (auto part : _parts)
		part->Update();

	for (auto slot : _slots)
		slot->Update();
	
	//KeyInput();
}

void Robot::Render()
{
	/*for (auto part : _parts)
	{
		part->Render();
	}*/
	_parts[P_BODY]->Render();
	_parts[P_NECK]->Render();
	_parts[P_HEAD]->Render();
	_parts[P_LEFT_EYE]->Render();
	_parts[P_RIGHT_EYE]->Render();
	_parts[P_ANTENNA_BODY]->Render();
	_parts[P_ANTENNA_HEAD]->Render();
	_parts[P_LEFT_SHOULDER]->Render();
	_parts[P_RIGHT_SHOULDER]->Render();
	_parts[P_LEFT_UPPER_ARM]->Render();
	_parts[P_RIGHT_UPPER_ARM]->Render();
	_parts[P_LEFT_ELBOW]->Render();
	_parts[P_RIGHT_ELBOW]->Render();
	_parts[P_LEFT_UNDER_ARM]->Render();
	_parts[P_RIGHT_UNDER_ARM]->Render();
	_parts[P_STOMACH]->Render();
	_parts[P_HIP]->Render();
	_parts[P_LEFT_HIPJOINT]->Render();
	_parts[P_RIGHT_HIPJOINT]->Render();
	_parts[P_LEFT_UPPER_LEG]->Render();
	_parts[P_RIGHT_UPPER_LEG]->Render();
	_parts[P_LEFT_KNEE]->Render();
	_parts[P_RIGHT_KNEE]->Render();
	_parts[P_LEFT_UNDER_LEG]->Render();
	_parts[P_RIGHT_UNDER_LEG]->Render();
}

void Robot::Initialize()
{
	//body
	{
		DiffuseCube* body = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(2.5, 1.5, 2));

		_parts.push_back(body);
	}
	//neck
	{
		DiffuseCube* neck = new DiffuseCube(XMFLOAT4(1, 1, 0, 1), Vector3(0.3, 0.3, 0.3));
		neck->_translation.y = 1;
		neck->SetParent(_parts[P_BODY]);

		_parts.push_back(neck);
	}
	//head
	{
		DiffuseCube* head = new DiffuseCube(XMFLOAT4(0.3, 0.3, 0.3, 1), Vector3(2, 1, 1.5));
		Transform* neckToHead = new Transform();

		neckToHead->SetParent(_parts[P_NECK]);
		neckToHead->_translation.y = 0.7f;

		head->SetParent(neckToHead);

		_parts.push_back(head);
		_slots.push_back(neckToHead);
	}
	//eye
	{
		DiffuseCube* leftEye = new DiffuseCube(XMFLOAT4(1.0, 0.0, 0.0, 1), Vector3(0.4, 0.2, 0.1));

		leftEye->SetParent(_parts[P_HEAD]);
		leftEye->_translation.z = 0.8f;
		leftEye->_translation.x = -0.5f;

		_parts.push_back(leftEye);

		DiffuseCube* rightEye = new DiffuseCube(XMFLOAT4(1.0, 0.0, 0.0, 1), Vector3(0.4, 0.2, 0.1));

		rightEye->SetParent(_parts[P_HEAD]);
		rightEye->_translation.z = 0.8f;
		rightEye->_translation.x = +0.5f;

		_parts.push_back(rightEye);
	}
	//antenna
	{
		DiffuseCube* antennaB = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.1, 0.5, 0.1));

		antennaB->SetParent(_parts[P_HEAD]);
		antennaB->_translation.y = 0.7f;

		_parts.push_back(antennaB);

		DiffuseCube* antennaH = new DiffuseCube(XMFLOAT4(1, 0, 0, 1), Vector3(0.2, 0.1, 0.2));

		antennaH->SetParent(_parts[P_HEAD]);
		antennaH->_translation.y = 1.0f;

		_parts.push_back(antennaH);
	}
	//shoulder
	{
		Transform* lSlot = new Transform();

		lSlot->_translation.x = -1.7f;
		lSlot->_translation.y = 0.5f;
		lSlot->SetParent(_parts[P_BODY]);
		_slots.push_back(lSlot);

		DiffuseCube* lShoulder = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.9, 0.7, 0.7));

		lShoulder->SetParent(lSlot);

		_parts.push_back(lShoulder);

		Transform* rSlot = new Transform();

		rSlot->_translation.x = 1.7f;
		rSlot->_translation.y = 0.5f;
		rSlot->SetParent(_parts[P_BODY]);
		_slots.push_back(rSlot);

		DiffuseCube* rShoulder = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.9, 0.7, 0.7));

		rShoulder->SetParent(rSlot);

		_parts.push_back(rShoulder);
	}

	{
		DiffuseCube* lUpperArm = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.4, 0.7, 0.4));
		lUpperArm->_translation.y = -0.7f;
		lUpperArm->_translation.x = -0.05f;
		lUpperArm->SetParent(_parts[P_LEFT_SHOULDER]);

		_parts.push_back(lUpperArm);

		DiffuseCube* rUpperArm = new DiffuseCube(XMFLOAT4(1, 1, 0.25, 1), Vector3(0.4, 0.7, 0.4));
		rUpperArm->_translation.y = -0.7f;
		rUpperArm->_translation.x = 0.05f;
		rUpperArm->SetParent(_parts[P_RIGHT_SHOULDER]);

		_parts.push_back(rUpperArm);
	}

	//Elbow
	{
		Transform* lSlot = new Transform();
		lSlot->_translation.y = -0.6f;
		lSlot->SetParent(_parts[P_LEFT_UPPER_ARM]);

		_slots.push_back(lSlot);

		DiffuseCube* leftElbow = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.7, 0.7, 0.7));
		leftElbow->_translation.y = -0.6f;
		leftElbow->SetParent(_parts[P_LEFT_UPPER_ARM]);

		_parts.push_back(leftElbow);

		Transform* rSlot = new Transform();
		rSlot->_translation.y = -0.6f;
		rSlot->SetParent(_parts[P_RIGHT_UPPER_ARM]);

		_slots.push_back(rSlot);

		DiffuseCube* rightElbow = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.7, 0.7, 0.7));
		rightElbow->_translation.y -= 0.6f;
		rightElbow->SetParent(_parts[P_RIGHT_UPPER_ARM]);

		_parts.push_back(rightElbow);
	}

	//UnderArm
	{
		DiffuseCube* lUnderArm = new DiffuseCube(XMFLOAT4(1, 1, 0.25, 1), Vector3(0.5, 1.0, 0.5));
		lUnderArm->_translation.y = -0.7f;
		lUnderArm->SetParent(_slots[S_LEFT_ELBOW]);

		_parts.push_back(lUnderArm);

		DiffuseCube* rUnderArm = new DiffuseCube(XMFLOAT4(1, 1, 0.25, 1), Vector3(0.5, 1.0, 0.5));
		rUnderArm->_translation.y -= 0.7f;
		rUnderArm->SetParent(_slots[S_RIGHT_ELBOW]);

		_parts.push_back(rUnderArm);
	}

	//Stomach
	{
		DiffuseCube* stomach = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.5, 1.0, 0.5));
		stomach->_translation.y = -1.0f;
		stomach->SetParent(_parts[P_BODY]);

		_parts.push_back(stomach);
	}

	//Hip
	{
		DiffuseCube* hip = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(1.5, 0.7, 1.5));
		hip->_translation.y = -1.0f;
		hip->SetParent(_parts[P_STOMACH]);

		_parts.push_back(hip);
	}

	//HipJoint
	{
		Transform* lSlot = new Transform();
		lSlot->_translation.x = -1.0f;
		lSlot->SetParent(_parts[P_HIP]);
		_slots.push_back(lSlot);

		DiffuseCube* lHipJoint = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.7, 0.5, 0.5));
		lHipJoint->_translation.x = -1.0f;
		lHipJoint->SetParent(_parts[P_HIP]);

		_parts.push_back(lHipJoint);

		Transform* rSlot = new Transform();
		rSlot->_translation.x = 1.0f;
		rSlot->SetParent(_parts[P_HIP]);
		_slots.push_back(rSlot);

		DiffuseCube* rHipJoint = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.7, 0.5, 0.5));
		rHipJoint->_translation.x = 1.0f;
		rHipJoint->SetParent(_parts[P_HIP]);

		_parts.push_back(rHipJoint);
	}

	//UpperLeg
	{
		DiffuseCube* lUpperLeg = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.4, 1.5, 0.4));
	
		lUpperLeg->_translation.y = -0.7f;
	
		lUpperLeg->SetParent(_slots[S_LEFT_HIPJOINT]);

		_parts.push_back(lUpperLeg);

		DiffuseCube* rUpperLeg = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.4, 1.5, 0.4));

		rUpperLeg->_translation.y = -0.7f;

		rUpperLeg->SetParent(_slots[S_RIGHT_HIPJOINT]);

		_parts.push_back(rUpperLeg);
	}

	//Knee
	{
		Transform* lSlot = new Transform();
		lSlot->_translation.y = -1.0f;
		lSlot->SetParent(_parts[P_LEFT_UPPER_LEG]);
		_slots.push_back(lSlot);

		DiffuseCube* lKnee = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.5, 0.5, 0.5));
		lKnee->_translation.y = -1.0f;
		lKnee->SetParent(_parts[P_LEFT_UPPER_LEG]);

		_parts.push_back(lKnee);

		Transform* rSlot = new Transform();
		rSlot->_translation.y = -1.0f;
		rSlot->SetParent(_parts[P_RIGHT_UPPER_LEG]);
		_slots.push_back(rSlot);

		DiffuseCube* rKnee = new DiffuseCube(XMFLOAT4(0.25, 0.25, 0.25, 1), Vector3(0.5, 0.5, 0.5));
		rKnee->_translation.y = -1.0f;
		rKnee->SetParent(_parts[P_RIGHT_UPPER_LEG]);

		_parts.push_back(rKnee);
	}

	//UnderLeg
	{
		DiffuseCube* lUnderLeg = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.4, 1.5, 0.4));

		lUnderLeg->_translation.y = -0.7f;

		lUnderLeg->SetParent(_slots[S_LEFT_KNEE]);

		_parts.push_back(lUnderLeg);

		DiffuseCube* rUnderLeg = new DiffuseCube(XMFLOAT4(1, 1, 0.0, 1), Vector3(0.4, 1.5, 0.4));

		rUnderLeg->_translation.y = -0.7f;

		rUnderLeg->SetParent(_slots[S_RIGHT_KNEE]);

		_parts.push_back(rUnderLeg);
	}
}

void Robot::KeyInput()
{
	if (KEY_PRESS('Q'))
		_parts[P_BODY]->_rotation.y +=  Time::Delta() * 5.0f;

	if (KEY_PRESS('E'))
		_parts[P_BODY]->_rotation.y -= Time::Delta() * 5.0f;

	if (KEY_PRESS('1'))
	{
		_slots[S_RIGHT_ELBOW]->_rotation.x = 0;
	}
	if (KEY_PRESS('2'))
	{
		
	}
	if (KEY_PRESS('3'))
	{
		_slots[S_LEFT_HIPJOINT]->_rotation.x = -90 * 3.141592f / 180.0f;
	}
	if (KEY_PRESS('4'))
	{
		_slots[S_RIGHT_HIPJOINT]->_rotation.x += Time::Delta() * 5.0f;
	}
	if (KEY_PRESS('5'))
	{
		_slots[S_LEFT_KNEE]->_rotation.x += Time::Delta() * 5.0f;
	}
	if (KEY_PRESS('6'))
	{
		_slots[S_RIGHT_KNEE]->_rotation.x += Time::Delta() * 5.0f;
	}

	if (KEY_PRESS('W'))
	{
		_parts[P_BODY]->_translation += _parts[P_BODY]->Forward() * Time::Delta() * 3.0f;

		Walk();
	}

	if (KEY_PRESS('A'))
		_parts[P_BODY]->_translation += _parts[P_BODY]->Left() * Time::Delta() * 3.0f;

	if (KEY_PRESS('S'))
	{
		_parts[P_BODY]->_translation += _parts[P_BODY]->Backward() * Time::Delta() * 3.0f;

		Walk();
	}

	if (KEY_PRESS('D'))
		_parts[P_BODY]->_translation += _parts[P_BODY]->Right() * Time::Delta() * 3.0f;

}

void Robot::Walk()
{
	_slots[S_LEFT_SHOULDER]->_rotation.x += Time::Delta() * _legSpeed * -1 * _direction1;
	_slots[S_RIGHT_SHOULDER]->_rotation.x += Time::Delta() * _legSpeed * _direction1;


	_slots[S_LEFT_HIPJOINT]->_rotation.x += Time::Delta() * _legSpeed * _direction1;
	_slots[S_RIGHT_HIPJOINT]->_rotation.x += Time::Delta() * _legSpeed * -1 * _direction1;

	if (_slots[S_LEFT_HIPJOINT]->_rotation.x < 0)
	{
		_slots[S_LEFT_KNEE]->_rotation.x += Time::Delta() * _underLegSpeed * -1 * _direction1;
		_slots[S_RIGHT_ELBOW]->_rotation.x += Time::Delta() * _underLegSpeed * _direction1;
	}
	else
	{
		_slots[S_LEFT_KNEE]->_rotation.x += Time::Delta() * _underLegSpeed * _direction1;
	}


	if (_slots[S_RIGHT_HIPJOINT]->_rotation.x < 0)
	{
		_slots[S_RIGHT_KNEE]->_rotation.x += Time::Delta() * _underLegSpeed * _direction1;
		_slots[S_LEFT_ELBOW]->_rotation.x += Time::Delta() * _underLegSpeed * -1 * _direction1;
	}
	else
	{
		_slots[S_RIGHT_KNEE]->_rotation.x += Time::Delta() * _underLegSpeed * -1 * _direction1;
	}



	if (_slots[S_LEFT_HIPJOINT]->_rotation.x >= _fistMaxAngle 
		|| _slots[S_RIGHT_HIPJOINT]->_rotation.x >= _fistMaxAngle)
		_direction1 *= -1;
}

void Robot::Idle()
{
	_slots[S_LEFT_SHOULDER]->_rotation.x = 0;
	_slots[S_RIGHT_SHOULDER]->_rotation.x = 0;

	_slots[S_LEFT_HIPJOINT]->_rotation.x = 0;
	_slots[S_RIGHT_HIPJOINT]->_rotation.x = 0;

	_slots[S_LEFT_KNEE]->_rotation.x = 0;
	_slots[S_LEFT_ELBOW]->_rotation.x = 0;

	_slots[S_RIGHT_ELBOW]->_rotation.x = 0;
	_slots[S_RIGHT_KNEE]->_rotation.x = 0;

	_direction1 = -1;
}
