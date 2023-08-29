#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_world = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	_world = XMMatrixTransformation
	(
		_pivot, XMQuaternionIdentity(), _scale,
		_pivot, XMQuaternionRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z),
		_translation
	);

	if (_parent != nullptr)
		_world *= _parent->GetWorld();

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, _world);

	_right	 = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	_up		 = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	_forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, _world);

	_globalScale = outS;
	_globalRotation = outR;
	_globalTranslation = outT;
}

void Transform::Debug()
{
	if (ImGui::BeginMenu(_label.c_str()))
	{
		ImGui::DragFloat3("Scale", (float*)&_scale, 0.01f, 0.01f, 100.0f);

		ImGui::SliderAngle("RotationX", &_rotation.x);
		ImGui::SliderAngle("RotationY", &_rotation.y);
		ImGui::SliderAngle("RotationZ", &_rotation.z);

		// 오일러각은 구현하기 쉽지만 짐벌락 현상이 나타나 3D에선 사용할 수 없다
		// 이에 대한 해결방법이 쿼터니언이다

		//ImGui::DragFloat3("Rotation",   (float*)&_rotation,     0.01f, -XM_2PI, XM_2PI);
		ImGui::DragFloat3("Translate", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}
