#pragma once
#include "Core/Component.h"

class Enemy : public Component
{
public:
	Enemy();
	void Update(const float _delta_time) override;
	void CreateBullet(Maths::Vector2f _position);

	float timer = 0.f;
};

