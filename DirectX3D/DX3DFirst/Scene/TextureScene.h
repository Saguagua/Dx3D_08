#pragma once
class TextureScene :public Scene
{
public:
	TextureScene();
	~TextureScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Robot* _robot;
	Cube* _cube;
	TextureCube* _tCube;
	QuadCube* _quadCube;
	Cylinder* _cylinder;
	Sphere* _sphere;
};

