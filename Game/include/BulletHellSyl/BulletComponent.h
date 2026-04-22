#pragma once
#include "Core/Component.h"

class BulletComponent : public Component
{
public:
	BulletComponent();
	void Update(float _delta_time) override;
	Maths::Vector2f randomDirection();

	float speed = 15.0f;
	Maths::Vector2f direction;
};

