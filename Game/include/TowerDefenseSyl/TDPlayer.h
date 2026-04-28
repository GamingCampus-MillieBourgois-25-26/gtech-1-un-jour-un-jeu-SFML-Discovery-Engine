#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/TextRenderer.h"
#include <string>

class TDPlayer : public Component
{
public:
	void Update(float _delta_time) override;
	int* GetGold();
	int gold = 10;
};

