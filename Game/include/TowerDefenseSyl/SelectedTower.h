#pragma once
#include "Core/Component.h"

class SelectedTower : public Component
{
public:
	void SetSelectedTower(char* comp);
	char* GetSelectedTower();

	char* select = nullptr;
};

