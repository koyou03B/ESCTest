#pragma once
#include <string>
#include"Component.h"
#include "ECS.h"

class Scene
{
private:
	Manager m_manager;

public:

	void Init()
	{
		auto& newPlayer(m_manager.AddEntity());
		newPlayer.AddComponent<PositionComponent>();
		newPlayer.GetComponent<PositionComponent>().SetPosition(10, 15);

		newPlayer.AddComponent<AngleComponent>();
		newPlayer.GetComponent<AngleComponent>().SetAngle(10);

		auto& newEnemy(m_manager.AddEntity());
		newEnemy.AddComponent<PositionComponent>();
		newEnemy.GetComponent<PositionComponent>().SetPosition(10, 15);

		newEnemy.AddComponent<AngleComponent>();
		newEnemy.GetComponent<AngleComponent>().SetAngle(10);
	}
	void Update()
	{
		m_manager.Update();
	};

	void Render()
	{
		m_manager.Render();
	}
	void Relese()
	{
		m_manager.Relese();
	};
};

inline Scene& GetScene()
{
	static Scene scene;
	return scene;
}