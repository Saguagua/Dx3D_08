// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <windows.h>

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define WIN_WIDTH 1280.0f
#define	WIN_HEIGHT 720.0f

//UI 사용자가 컴퓨터에 명령을 내릴 수 있게 하는 것

//DX 그래픽과 스피드 상승을 위해 등장

//컴파일 단계에서 cpp을 읽는다. h는 읽지 않는다
//인라인 함수 = 메크로와 같이 전처리 단계에서 치환