#include "framework.h"
#include "TerrianScene.h"

TerrianScene::TerrianScene()
{
	_terrian = new Terrian(L"Landscape/Dirt.png", L"HeightMap/HeightMap256.png");
}

TerrianScene::~TerrianScene()
{
	delete _terrian;
}

void TerrianScene::CreateMesh()
{
	
	
}

void TerrianScene::Update()
{
	_terrian->Update();
}

void TerrianScene::PreRender()
{
}

void TerrianScene::Render()
{
	_terrian->Render();
}

void TerrianScene::PostRender()
{
}
