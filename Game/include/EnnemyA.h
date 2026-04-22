#pragma once
#include "Core/Component.h"

class EnnemyA : public Component
{
public:
	void Update(const float _delta_time) override;
	void CreateBullet();

	float timer = 0.2f;
};

