#pragma once
#include "Core/Component.h"

class PriceDisplay : public Component
{
public:
	PriceDisplay(unsigned int* pric);
	void Update(float _delta_time) override;

	unsigned int* price;
};

