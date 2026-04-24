#pragma once
#include "Modules/InputModule.h"
#include "Core/Component.h"

class Pink : public Component
{
public:
	Pink(InputModule* inpu, unsigned int* scor);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	float timer = 1.f;
	int level = 0;
	unsigned int* score;
	unsigned int cost = 100;
	float size = 76.f;
	InputModule* input;
};

