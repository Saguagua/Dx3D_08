#pragma once
class Scene
{
public:
	//생성자는 생성될 때 호출되는 함수
	virtual ~Scene() = default;

	virtual void Update() abstract;

	virtual void PreRender() abstract;
	//화면 쪼개기 같은 사전작업
	virtual void Render() abstract;
	virtual void PostRender() abstract;
};

