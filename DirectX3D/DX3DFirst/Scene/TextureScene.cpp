#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_robot = new Robot();
}

TextureScene::~TextureScene()
{
	delete _robot;
}

void TextureScene::Update()
{
	_robot->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_robot->Render();
}

void TextureScene::PostRender()
{
}
