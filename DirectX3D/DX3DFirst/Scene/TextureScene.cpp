#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	//_cube = new TextureCube();
	//_cube->SetLabel("Cube");
	//_robot = new Robot();
	//_cylinder = new Cylinder(5, 5, 10, 5, 5);
	//_cylinder->_translation = Vector3(0, 0, 0);
	Camera::GetInstance()->_transform->_translation = Vector3(0, 0, 0);
	_sphere = new Sphere(10, 20, 20);

	_sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	_sphere->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");
	//_cube = new Cube({ 1, 0, 0, 1 }, {1,1,1});
	//_cube->_translation.x = 10.0f;
	//_tCube = new TextureCube();
}

TextureScene::~TextureScene()
{
	//delete _cube;
	//delete _robot;
	//delete _cylinder;
	//delete _sphere;
	//delete _cube;
	//delete _tCube;
}

void TextureScene::Update()
{
	//_cube->Update();
	//_tCube->Update();
	//_robot->Update();
	//_cylinder->Update();
	_sphere->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	//_cube->Render();
	//_tCube->Render();
	//_robot->Render();
	//RS->ChangeState(D3D11_FILL_WIREFRAME);
	_sphere->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);

}

void TextureScene::PostRender()
{
	//_cube->Debug();
	_sphere->GetMaterial()->PostRender();
}
