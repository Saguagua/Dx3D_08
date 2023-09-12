#pragma once
class TerrainScene :public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	float _angle;
	bool _move = false;
	Vector3 _direction;
	Vector3 _pickedPostion;
	Terrain* _terrain;
	Robot* _robot;
};

//빛
// Specilar  정반사 :
// Diffuse   난반사 :
// Ambient 주변반사 :
// 
// 태양은 평행한 빛으로 취급
// normal Vector : 지면과 수직인 벡터 -> 외적으로 구한다
// 법선 벡터를 구하고 빛과의 사이 각을 구한다 사이 각이 클 수록 빛의 손실이 커진다
//