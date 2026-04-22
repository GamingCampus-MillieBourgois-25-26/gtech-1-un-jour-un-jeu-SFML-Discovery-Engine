#pragma once
#include "Core/Component.h"
#include "InputModule.h"
class EnnemieMouve : public Component
{
	

public:


	void Update(const float _delta_time) override {
		Maths::Vector2<float> position = GetOwner()->GetPosition();

		
			position.y += speed * _delta_time;
		
		

		GetOwner()->SetPosition(position);
	}


	float speed = 10.0f;
};

