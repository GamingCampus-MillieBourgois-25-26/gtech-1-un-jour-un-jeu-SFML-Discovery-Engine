#pragma once
#include "Core/Component.h"

class BulletComponent : public Component
{
public:
	BulletComponent();
	void Update(float _delta_time) override;
	Maths::Vector2f randomDirection();

	float speed = 10.0f;
	float lifeTime = 10.f;
	Maths::Vector2f direction;
};

