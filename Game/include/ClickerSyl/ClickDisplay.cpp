#include "ClickDisplay.h"

void ClickDisplay::Update(float _delta_time)
{
	lifetime -= _delta_time;
	if (lifetime <= 0)
	{
		GetOwner()->Destroy();
	}
	position.y -= speed * _delta_time;
}