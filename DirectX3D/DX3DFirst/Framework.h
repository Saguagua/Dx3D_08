// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>
#include <DirectXCollision.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "")
//라이브러리는 cpp파일이 없거나 기본 설정으로 읽어오지 않을 때 사용한다.
//라이브러리는 cpp를 기계어로 번역된 파일

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "ImGui.lib")

using namespace std;
using namespace DirectX;


#include "DirectXTex.h"
#include "DirectXTex.inl"

#pragma comment(lib, "DirectXTex.lib")

#define WIN_WIDTH 1280.0f
#define	WIN_HEIGHT 720.0f

#define DEVICE Device::GetInstance()->GetDevice()
#define DC	   Device::GetInstance()->GetDeviceContext()

#define KEY_UP(p)	 Keyboard::GetInstance()->Up(p)
#define KEY_DOWN(p)	 Keyboard::GetInstance()->Down(p)
#define KEY_PRESS(p) Keyboard::GetInstance()->Press(p)

#define RS StateManager::GetInstance()->GetRS()

typedef XMMATRIX Matrix;
typedef XMFLOAT4 Vector4;
typedef XMFLOAT2 Vector2;

#include "Utility/Singleton.h"
#include "Utility/Vector3.h"
#include "Utility\Keyboard.h"
#include "Utility\Time.h"
#include "Utility\Utility.h"
#include "Object/Transform.h"

using namespace Utility;

#include "System/Device.h"

#include "Render/Shader/Shader.h"
#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"

#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"

#include "Render\Texture\Texture.h"
#include "Render/Mesh.h"
#include "Render/Material.h"

#include "Render\State\SamplerState.h"
#include "Render\State\RasterizerState.h"
#include "Render\State\StateManager.h"

#include "System\Camera.h"
#include "System/Environment.h"

#include "Object/Basic\Cube.h"
#include "Object/Basic/Quad.h"
#include "Object\Basic\QuadCube.h"
#include "Object\Basic\TextureCube.h"
#include "Object/Basic/DiffuseCube.h"
#include "Object/Basic/Cylinder.h"
#include "Object/Basic/Sphere.h"

#include "Object\LandScape\Terrian.h"
#include "Object\LandScape\TerrainEditor.h"

#include "Object/Robot/Robot.h"

#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"
#include "Scene\TextureScene.h"
#include "Scene\TerrianScene.h"
#include "Scene\TerrainEditorScene.h"
#include "MainGame.h"


extern HWND _hWnd;
extern Vector3 _mousePos;


//UI 사용자가 컴퓨터에 명령을 내릴 수 있게 하는 것

//DX 그래픽과 스피드 상승을 위해 등장

//컴파일 단계에서 cpp을 읽는다. h는 읽지 않는다
//인라인 함수 = 메크로와 같이 전처리 단계에서 치환