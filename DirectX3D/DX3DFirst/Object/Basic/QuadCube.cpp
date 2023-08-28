#include "framework.h"
#include "QuadCube.h"

QuadCube::QuadCube(Vector3 size)
{
	//F
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.z += size.z * 0.5f; 
		quad->_rotation.x += 3.141592f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}
	
	//B
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.z -= size.z * 0.5f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}

	//T
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.y += size.y * 0.5f;
		quad->_rotation.x += 90.0f * 3.141592f / 180.0f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}

	//D
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.y -= size.y * 0.5f;
		quad->_rotation.x -= 90.0f * 3.141592f / 180.0f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}

	//L
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.x -= size.x * 0.5f;
		quad->_rotation.y = 90.0f * 3.141592f / 180.0f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}

	//R
	{
		Quad* quad = new Quad(Vector2(size.x, size.y));
		quad->_translation.x += size.x * 0.5f;
		quad->_rotation.y -= 90.0f * 3.141592f / 180.0f;
		quad->SetParent(this);
		_surfaces.push_back(quad);
	}
}

QuadCube::~QuadCube()
{
	for (int i = 0; i < _surfaces.size(); i++)
	{
		delete _surfaces[i];
	}

	_surfaces.clear();
}

void QuadCube::Render()
{
	for (int i = 0; i < _surfaces.size(); i++)
	{
		_surfaces[i]->Render();
	}
}

void QuadCube::Update()
{
	Transform::Update();

	for (int i = 0; i < _surfaces.size(); i++)
	{
		_surfaces[i]->Update();
	}

	KeyInput();
}

void QuadCube::KeyInput()
{

	if (KEY_PRESS('W'))
		_rotation.x += Time::Delta();

	if (KEY_PRESS('S'))
		_rotation.x -= Time::Delta();

	if (KEY_PRESS('D'))
		_rotation.y += Time::Delta();

	if (KEY_PRESS('A'))
		_rotation.y -= Time::Delta();

	if (KEY_PRESS(VK_RIGHT))
		_translation += Right() * Time::Delta();
	if (KEY_PRESS(VK_LEFT))
		_translation += Left() * Time::Delta();
	if (KEY_PRESS(VK_UP))
		_translation += Up() * Time::Delta();
	if (KEY_PRESS(VK_DOWN))
		_translation += Down() * Time::Delta();
}
