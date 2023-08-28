#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	//_robot = new Robot();
	_quad = new Quad();
	_quadCube = new QuadCube();
}

TextureScene::~TextureScene()
{
	//delete _robot;
	delete _quad;
	delete _quadCube;
}

void TextureScene::Update()
{
	//_robot->Update();
	//_quad->Update();
	_quadCube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	//_robot->Render();
	//_quad->Render();
	_quadCube->Render();
}

void TextureScene::PostRender()
{
}
