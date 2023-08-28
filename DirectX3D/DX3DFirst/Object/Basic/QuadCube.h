#pragma once
class QuadCube :public Transform
{
public:
	QuadCube(Vector3 size = Vector3(1.0f, 1.0f, 1.0f));
	~QuadCube();

	void Render();
	void Update();

private:
	void KeyInput();

	vector<Quad*> _surfaces;

};

