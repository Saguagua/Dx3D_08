#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	//_cube = new TextureCube();
	//_cube->SetLabel("Cube");
	//_robot = new Robot();
	//_cylinder = new Cylinder(5, 5, 10, 5, 5);
	//_cylinder->_translation = Vector3(0, 0, 0);
	_sphere = new Sphere(10, 20, 20);
}

TextureScene::~TextureScene()
{
	//delete _cube;
	//delete _robot;
	//delete _cylinder;
	delete _sphere;
}

void TextureScene::Update()
{
	//_cube->Update();
	//_robot->Update();
	//_cylinder->Update();
	_sphere->Update();

	if (KEY_PRESS('Q'))
		_sphere->_rotation.z += Time::Delta() * 10.0f;
	if (KEY_PRESS('E'))
		_sphere->_rotation.z -= Time::Delta() * 10.0f;
	if (KEY_PRESS('W'))
		_sphere->_translation.z += Time::Delta() * 10.0f;
	if (KEY_PRESS('S'))
		_sphere->_translation.z -= Time::Delta() * 10.0f;
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	//_cube->Render();
	//_robot->Render();
	_sphere->Render();
}

void TextureScene::PostRender()
{
	//_cube->Debug();
}
