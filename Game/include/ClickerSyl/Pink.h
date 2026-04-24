#pragma once
#include "Core/Component.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"

class Pink : public Component
{
public:
	Pink(InputModule* inpu, WindowModule* windo);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	InputModule* input;
	WindowModule* window;
	float size = 76.f;
};

