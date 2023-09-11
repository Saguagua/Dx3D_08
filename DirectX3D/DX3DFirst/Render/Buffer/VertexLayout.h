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

	VertexTextureNormal(Vector3 pos, Vector2 uv, Vector3 normal)
		: _pos(pos), _uv(uv), _normal(normal) 
	{}

	Vector3 _pos = {};
	Vector2 _uv = {};
	Vector3 _normal = {};
};

struct VertexColorNormal
{
	VertexColorNormal() {}
	VertexColorNormal(XMFLOAT4 color, XMFLOAT3 pos)
	: _color(color), _pos(pos){}

	VertexColorNormal(XMFLOAT4 color, XMFLOAT3 pos, Vector3 normal)
		: _color(color), _pos(pos), _normal(normal) {}

	Vector3 _pos = {};
	Vector4 _color = {};
	Vector3 _normal = {};
};


struct VertexTextureNormalTangent
{
	VertexTextureNormalTangent() {}

	VertexTextureNormalTangent(Vector3 pos, Vector2 uv, Vector3 normal, Vector3 tangent)
		: _pos(pos), _uv(uv), _normal(normal), _tangent(tangent) {}

	Vector3 _pos = {};
	Vector2 _uv = {};
	Vector3 _normal = {};
	Vector3 _tangent = {};
};