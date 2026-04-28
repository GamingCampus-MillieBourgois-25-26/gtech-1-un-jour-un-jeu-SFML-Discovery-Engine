#pragma once
#include "Core/Component.h"
#include "TowerDefenseSyl/TowerSelection.h"
#include "ProjectileComponent.h"
#include "Components/SpriteRenderer.h"
#include "Modules/AssetsModule.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <iostream>

class Tower : public Component
{
public:
	Tower(Type towerType);
	void Update(float _delta_time) override;
	void shot(GameObject* obj);
	GameObject* FindTarget();

	Type type;
	int damage;
	float atkSpeed;
	float reload;
	float range;
};

