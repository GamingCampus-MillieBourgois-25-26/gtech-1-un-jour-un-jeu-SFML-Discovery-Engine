#pragma once
#include "Core/Component.h"

class SmallBullet : public Component
{
public:
	SmallBullet();
	void Update(float _delta_time) override;
	Maths::Vector2f randomDirection();

	float speed = 100.0f;
	Maths::Vector2f direction;
};

