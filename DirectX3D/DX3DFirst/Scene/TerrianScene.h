#pragma once
class TerrianScene :public Scene
{
public:
	TerrianScene();
	~TerrianScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void CreateMesh();

	Terrian* _terrian;
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