#pragma once
#include "Core/Component.h"
#include "ClickerController.h"
#include "Maths/Vector2.h"


class ClickerButton : public Component
{
public: 
	void SetController(ClickerController* controller);
	void Update(float _delta_time) override;

private:
	ClickerController* controller = nullptr;
	Maths::Vector2f size = Maths::Vector2f(130.f, 130.f);

};

