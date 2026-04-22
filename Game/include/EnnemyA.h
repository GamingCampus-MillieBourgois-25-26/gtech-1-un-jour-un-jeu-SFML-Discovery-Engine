#pragma once
#include "Core/Component.h"

class EnnemyA : public Component
{
public:
	EnnemyA();
	void Update(const float _delta_time) override;
	void CreateBullet(Maths::Vector2f _position);

	float timer = 0.f;
};

