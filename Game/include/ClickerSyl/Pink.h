#pragma once
#include "Modules/InputModule.h"
#include "Core/Component.h"
#include "Core/GameObject.h"

class Pink : public Component
{
public:
	Pink(InputModule* inpu, unsigned int* scor);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	float timer = 0.5f;
	int level = 0;
	unsigned int* score;
	unsigned int cost = 100;
	float size = 76.f;
	InputModule* input;
};

