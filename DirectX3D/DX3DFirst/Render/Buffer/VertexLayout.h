#pragma once
struct Vertex
{
	Vertex() {}

	Vertex(float x, float y, float z)
	{
		pos = XMFLOAT3(x, y, z);
	}

	XMFLOAT3 pos = {};
};

struct VertexColor
{
	VertexColor() {}

	VertexColor(XMFLOAT4 color, XMFLOAT3 pos)
		:_color(color), _pos(pos)
	{}

	XMFLOAT3 _pos = {};
	XMFLOAT4 _color = {};
};

struct VertexTexture
{
	VertexTexture() {}

	VertexTexture(XMFLOAT3 pos, XMFLOAT2 uv)
		: _pos(pos), _uv(uv)
	{}

	Vector3 _pos = {};
	Vector2 _uv = {};
};

struct VertexTextureNormal
{
	VertexTextureNormal() {}

	Vector3 _pos = {};
	Vector2 _uv = {};
	Vector3 _normal = {};
};

struct VertexColorNormal
{
	VertexColorNormal() {}
	VertexColorNormal(XMFLOAT4 color, XMFLOAT3 pos)
	: _color(color), _pos(pos){}

	Vector3 _pos = {};
	Vector4 _color = {};
	Vector3 _normal = {};
};