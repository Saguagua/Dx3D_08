#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_cube = new TextureCube();
	_cube->SetLabel("Cube");
}

TextureScene::~TextureScene()
{
	delete _cube;
}

void TextureScene::Update()
{
	_cube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_cube->Render();
}

void TextureScene::PostRender()
{
	_cube->Debug();
}
