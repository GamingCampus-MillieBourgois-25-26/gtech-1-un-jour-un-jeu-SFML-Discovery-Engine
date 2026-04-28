#pragma once
#include "Core/Component.h"
#include "Maths/vector2.h"
#include "Core/GameObject.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(GameObject* obj);
	void Update(float _delta_time) override;

private:
	float speed = 400.f;
	GameObject* target;
	Maths::Vector2f pos;
	int damage = 1;
};