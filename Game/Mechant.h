#pragma once
#include "Core/Component.h"
#include "InputModule.h"

class Mechant : public Component
{
private:
	int max_hp;
	int hp;
	int ms;
public:
	void Update() {
		Maths::Vector2<float> position = GetOwner()->GetPosition();
		GetOwner()->SetPosition(position);
	}
};

