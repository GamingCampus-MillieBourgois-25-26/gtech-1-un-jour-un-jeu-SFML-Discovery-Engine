#pragma once
#include "Component.h"
#include <Scene.h>

class EnemyManager : public Component
{
private:
	std::vector<GameObject*> Enemies;
public:
	void Start() override {
		Scene* scene = GetOwner()->GetScene();

		for (int i = 0; i < 3; i++)
		{
			GameObject* soldier = scene->FindGameObject("SoldierGreen" + std::to_string(i));
			Enemies.push_back(soldier);
		}
	}
};

