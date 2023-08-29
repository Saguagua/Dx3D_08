#pragma once
class TextureCube :public Transform
{
	enum Side
	{
		L,
		R,
		D,
		U,
		F,
		B
	};
public:
	TextureCube();
	~TextureCube();

	void Update();
	void Render();

private:
	void CreateQuads();
	vector<Quad*> _quads;

};

