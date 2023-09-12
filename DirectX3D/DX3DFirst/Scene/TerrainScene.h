#pragma once
class TerrainScene :public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	// Scene��(��) ���� ��ӵ�
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

//��
// Specilar  ���ݻ� :
// Diffuse   ���ݻ� :
// Ambient �ֺ��ݻ� :
// 
// �¾��� ������ ������ ���
// normal Vector : ����� ������ ���� -> �������� ���Ѵ�
// ���� ���͸� ���ϰ� ������ ���� ���� ���Ѵ� ���� ���� Ŭ ���� ���� �ս��� Ŀ����
//