#include "ClickerDisplay.h"

void ClickerDisplay::Update(float _delta_time)
{
	lifetime -= _delta_time;
	if (lifetime <= 0)
	{
		GetOwner()->Disable();
	}
	Maths::Vector2f pos = GetOwner()->GetPosition();
	pos.y -= speed * _delta_time;
	GetOwner()->SetPosition(pos);
}
