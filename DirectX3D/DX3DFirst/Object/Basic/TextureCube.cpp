#include "framework.h"
#include "TextureCube.h"

TextureCube::TextureCube()
{
	CreateQuads();
}

TextureCube::~TextureCube()
{
	for (Quad* quad : _quads)
		delete quad;

	_quads.clear();
}

void TextureCube::Update()
{
	Transform::Update();

	for (Quad* quad : _quads)
		quad->Update();
}

void TextureCube::Render()
{
	for (Quad* quad : _quads)
		quad->Render();
}

void TextureCube::CreateQuads()
{
	_quads.resize(6);

	_quads[L] = new Quad();
	_quads[L]->_translation.x = -0.5f;
	_quads[L]->_rotation.y = XM_PIDIV2; //각 축의 회전은 + 에서 - 으로 가는 시계방향이다
	_quads[L]->SetParent(this);

	_quads[R] = new Quad();
	_quads[R]->_translation.x = 0.5f;
	_quads[R]->_rotation.y = -XM_PIDIV2;
	_quads[R]->SetParent(this);

	_quads[D] = new Quad();
	_quads[D]->_translation.y = -0.5f;
	_quads[D]->_rotation.x = -XM_PIDIV2;
	_quads[D]->SetParent(this);

	_quads[U] = new Quad();
	_quads[U]->_translation.y = 0.5f;
	_quads[U]->_rotation.x = XM_PIDIV2;
	_quads[U]->SetParent(this);

	_quads[F] = new Quad();
	_quads[F]->_translation.z = -0.5f;
	_quads[F]->SetParent(this);

	_quads[B] = new Quad();
	_quads[B]->_translation.z = 0.5f;
	_quads[B]->_rotation.y = -XM_PI;
	_quads[B]->SetParent(this);
}