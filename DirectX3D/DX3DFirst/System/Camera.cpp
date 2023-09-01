#include "framework.h"
#include "Camera.h"

Camera::Camera()
{
	_viewBuffer = new MatrixBuffer();
	_transform = new Transform();

	_transform->_translation = { 120.0f, 150.0f, -100.0f };
	_transform->_rotation.x = 0.6f;
}

Camera::~Camera()
{
	delete _transform;
	delete _viewBuffer;
}

void Camera::Update()
{
	_transform->Update();
	FreeMode();
}

void Camera::PostRender()
{
	Vector3 pos = _transform->_translation;
	Vector3 rot = _transform->_rotation;

	ImGui::Text("Camera Pos : %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);
	ImGui::Text("Camera Rot : %.2f, %.2f, %.2f", rot.x, rot.y, rot.z);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS(VK_LSHIFT))
			_moveSpeed = 50.0f;
		else
			_moveSpeed = 20.0f;

		if (KEY_PRESS('A'))
			_transform->_translation +=     _transform->Left() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('D'))
			_transform->_translation +=    _transform->Right() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('S'))
			_transform->_translation += _transform->Backward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('W'))
			_transform->_translation +=  _transform->Forward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('Q'))
			_transform->_translation +=       _transform->Up() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('E'))
			_transform->_translation +=     _transform->Down() * _moveSpeed * Time::Delta();

		Vector3 dir = _mousePos - _oldPos;

		_transform->_rotation.y += dir.x * _rotSpeed * Time::Delta();
		_transform->_rotation.x += dir.y * _rotSpeed * Time::Delta();
	}

	_oldPos = _mousePos;

	SetView();
}

void Camera::TargetMode()
{
}

void Camera::SetView()
{

	XMVECTOR   eyePos = _transform->_translation;
	XMVECTOR focusPos = _transform->_translation + _transform->Forward();
	XMVECTOR upVector = _transform->Up();

	_viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);
	//원근감과 카메라 회전을 위해 사용

	_viewBuffer->SetData(_viewMatrix);
	_viewBuffer->SetVSBuffer(1);
}
