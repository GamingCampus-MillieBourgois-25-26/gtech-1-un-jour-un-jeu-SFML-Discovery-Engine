#pragma once
#include "Core/Component.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(Maths::Vector2f position, Maths::Vector2f inTarget);
	void Update(float _delta_time) override;

private:
	float speed = 160.f;
	Maths::Vector2f target;
};