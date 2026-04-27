#pragma once
#include "Core/Component.h"
#include "Maths/vector2.h"
#include "Core/GameObject.h"

class ClickDisplay : Component
{
public:
	void Update(float _delta_time) override;

	Maths::Vector2f position = { 200.f, 200.f };
	float lifetime = 2.f;
	float speed = 10.f;
};

