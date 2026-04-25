#pragma once
#include "Core/Component.h"

class HQComponent : public Component
{
public:
	HQComponent();
	void TakeDamage();
	void Init();
	void Update(float _delta_time) override;

	int hp = 3;
	bool init = false;
	GameObject* life;
	GameObject* final = nullptr;
};

