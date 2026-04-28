#pragma once
#include "Core/Component.h"

enum class Type;

class SelectedTower : public Component
{
public:
	void SetSelectedTower(Type* comp);
	Type* GetSelectedTower();

	Type* select = nullptr;
};

