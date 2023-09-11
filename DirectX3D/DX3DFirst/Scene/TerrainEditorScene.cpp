#include "framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	_terrainEditor = new TerrainEditor();
	_terrainEditor->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	_terrainEditor->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	_terrainEditor->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete _terrainEditor;
}

void TerrainEditorScene::Update()
{
	_terrainEditor->Update();
	if (KEY_DOWN(VK_LBUTTON))
		_terrainEditor->Picking(&_pickedPostion);
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
	_terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{
	_terrainEditor->Debug();

	ImGui::Text("PickPos : %.001f, %.001f, %.001f", _pickedPostion.x, _pickedPostion.y, _pickedPostion.z);
}
