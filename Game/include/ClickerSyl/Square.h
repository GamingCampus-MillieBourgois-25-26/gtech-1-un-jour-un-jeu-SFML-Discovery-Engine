#pragma once
#include "Core/Component.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"

class Square : public Component
{
public:
	Square(InputModule* inpu, WindowModule* windo);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	int score = 0;
	InputModule* input;
	WindowModule* window;
	float size = 76.f;
	int click = 1;
};

