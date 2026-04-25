#pragma once
#include "Core/Component.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(GameObject* obj);
	void Update(float _delta_time) override;

private:
	float speed = 400.f;
	GameObject* target;
	Maths::Vector2f pos;
};