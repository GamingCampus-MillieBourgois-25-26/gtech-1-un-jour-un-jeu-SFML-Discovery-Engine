#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/TextRenderer.h"

class EndGame : public Component
{
public:
	void End(bool end);

	GameObject* display = nullptr;
};

