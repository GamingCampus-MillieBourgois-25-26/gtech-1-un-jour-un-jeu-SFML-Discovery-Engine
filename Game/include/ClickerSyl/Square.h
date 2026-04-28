#pragma once
#include "Core/Component.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"

class Square : public Component
{
public:
	Square(InputModule* inpu, WindowModule* windo, unsigned int* scor, unsigned int* clic);
	void Init();
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	unsigned int* score;
	InputModule* input;
	WindowModule* window;
	GameObject* display;
	float size = 76.f;
	unsigned int* click;
};

