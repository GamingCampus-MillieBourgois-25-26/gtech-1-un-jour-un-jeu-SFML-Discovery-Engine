#pragma once
#include "Core/Component.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(Maths::Vector2f inTarget);
	void Update(float _delta_time) override;

private:
	float speed = 20.f;
	Maths::Vector2f target;
};