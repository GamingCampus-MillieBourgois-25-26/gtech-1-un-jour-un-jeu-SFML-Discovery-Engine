#pragma once
#include "Core/Component.h"

class ClickerDisplay : public Component
{
public:
	void Update(float _delta_time) override;

	float lifetime = 1.f;
	float speed = 25.f;
};

