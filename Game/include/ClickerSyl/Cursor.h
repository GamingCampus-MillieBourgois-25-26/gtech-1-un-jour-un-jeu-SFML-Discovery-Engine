#pragma once
#include "Core/Component.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h"

class Cursor : public Component
{
public:
	Cursor(InputModule* inpu, WindowModule* windo, unsigned int* scor, unsigned int* clic);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	InputModule* input;
	WindowModule* window;
	float size = 76.f;
	unsigned int* score;
	unsigned int* click;
	unsigned int cost = 10;
};

