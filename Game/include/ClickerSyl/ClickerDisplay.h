#pragma once
#include "Core/Component.h"
#include "Maths/vector2.h"
#include "Core/GameObject.h"

class ClickerDisplay : public Component
{
public:
	void Update(float _delta_time) override;

	float lifetime = 1.f;
	float speed = 25.f;
};

