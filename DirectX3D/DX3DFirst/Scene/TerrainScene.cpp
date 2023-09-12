#include "framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap256.png");
	_robot = new Robot();
	_robot->GetBody()->_translation.x = 1;
}

TerrainScene::~TerrainScene()
{
	delete _terrain;
	delete _robot;
}



void TerrainScene::Update()
{
	_terrain->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		_terrain->Picking(&_pickedPostion);
		_move = true;

		_direction = _pickedPostion - (_robot->GetBody()->_translation + Vector3(0, -5, 0));
		_direction.Normalize();

		Vector2 robotXZ(_robot->GetBody()->Forward().x, _robot->GetBody()->Forward().z);

		float length = sqrt(robotXZ.x * robotXZ.x + robotXZ.y * robotXZ.y);
		robotXZ.x = robotXZ.x / length;
		robotXZ.y = robotXZ.y / length;

		_angle = _direction.x * robotXZ.x + _direction.z * robotXZ.y;

		_angle = acos(_angle);
		_robot->GetBody()->_rotation.y += _angle;
		_robot->Update();
	}

	if (_move)
	{
		_robot->GetBody()->_translation += _direction * 20.0f * Time::Delta();

		_robot->Walk();
		
		if (((_pickedPostion - (_robot->GetBody()->_translation + Vector3(0, -5, 0))).z < 0.5f) &&
			(_pickedPostion - (_robot->GetBody()->_translation + Vector3(0, -5, 0))).z > -0.5f)
		{
			_move = false;
			_robot->Idle();
		}
	}

	_robot->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	_terrain->Render();
	_robot->Render();
}

void TerrainScene::PostRender()
{
	_terrain->GetMaterial()->PostRender();

	ImGui::Text("PickPos : %.001f, %.001f, %.001f", _pickedPostion.x, _pickedPostion.y, _pickedPostion.z);
	ImGui::Text("Angle : %.001f", _angle);
}
