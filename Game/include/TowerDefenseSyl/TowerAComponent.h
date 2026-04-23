#pragma once
#include "Core/Component.h"


class TowerAComponent : public Component
{
public:
	TowerAComponent();
	void Update(float _delta_time) override;
	GameObject* FindTarget();
	void shot(GameObject* obj);

	int damage = 1;
	float atkSpeed = 0.5f;
	float reload = 0.f;
	float range = 200.f;
};

