#pragma once
class Scene
{
public:
	//�����ڴ� ������ �� ȣ��Ǵ� �Լ�
	virtual ~Scene() = default;

	virtual void Update() abstract;

	virtual void PreRender() abstract;
	//ȭ�� �ɰ��� ���� �����۾�
	virtual void Render() abstract;
	virtual void PostRender() abstract;
};

