#pragma once
struct Vertex
{
	Vertex(float x, float y, float z)
	{
		pos = XMFLOAT3(x, y, z);
	}

	XMFLOAT3 pos;
};

struct VertexColor
{
	VertexColor(XMFLOAT4 color, XMFLOAT3 pos)
		:_color(color), _pos(pos)
	{}

	XMFLOAT3 _pos;
	XMFLOAT4 _color;
};