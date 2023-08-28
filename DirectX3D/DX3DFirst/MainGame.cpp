#include "framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	_scene = new TextureScene();
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Update()
{
	Keyboard::GetInstance()->Update();
	Time::GetInstance()->Update();
	_scene->Update();
}

void MainGame::Render()
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	_scene->PreRender();

	Device::GetInstance()->Clear();

	_scene->Render();

	_scene->PostRender();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
		  Device::GetInstance();
	 Environment::GetInstance();
		Keyboard::GetInstance();
			Time::GetInstance();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void MainGame::Release()
{
	Environment::Delete();
	Shader::Delete();
	Device::Delete();
	Keyboard::Delete();
	Time::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}