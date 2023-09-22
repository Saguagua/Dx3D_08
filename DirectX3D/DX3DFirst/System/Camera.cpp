#include "framework.h"
#include "Camera.h"

Camera::Camera()
{
	_viewBuffer = new ViewBuffer();
	_transform = new Transform();

	_transform->_translation = { 60.0f, 60.0f, -10.0f };
	_transform->_rotation.x = 0.6f;

	Load();
}

Camera::~Camera()
{
	Save();
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

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
	Ray ray;
	ray.origin = _transform->_translation;

	///InvViewport

	Vector3 point; //left top이 0인 기준으로 작성함
	point.x = +(2.0f * screenPos.x) / WIN_WIDTH - 1.0f;
	point.y = -(2.0f * screenPos.y) / WIN_HEIGHT + 1.0f;
	point.z = 1.0f;

	///InvProj
	Matrix projection = Environment::GetInstance()->GetProjectionMatrix();

	XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, projection);

	point.x /= proj._11;
	point.y /= proj._22;

	///InvView

	Matrix invView = _transform->GetWorld();

	ray.direction = point* invView;
	ray.direction.Normalize();

	return ray;
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

	_viewBuffer->SetData(_viewMatrix, _transform->GetWorld());
	_viewBuffer->SetVSBuffer(1);
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(_transform->_scale);
	data.WriteData(_transform->_rotation);
	data.WriteData(_transform->_translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	_transform->_scale		 = data.ReadVector3();
	_transform->_rotation	 = data.ReadVector3();
	_transform->_translation = data.ReadVector3();
}
