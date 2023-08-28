#pragma once
class TextureScene :public Scene
{
public:
	TextureScene();
	~TextureScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Robot* _robot;
	Quad* _quad;
	QuadCube* _quadCube;
};

