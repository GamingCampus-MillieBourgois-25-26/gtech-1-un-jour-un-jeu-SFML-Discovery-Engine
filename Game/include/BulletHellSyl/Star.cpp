#include "pch.h"
#include "Star.h"
#include "Components/SquareCollider.h"
#include <iostream>

Star::Star(GameObject* obj)
{
	player = obj;
}

Star::Star(GameObject* obj, Star* prev)
{
	player = obj;
	prev->SetNext(this);
}

void Star::Update(const float _delta_time)
{
	if (SquareCollider::IsColliding(*player->GetComponent<SquareCollider>(), *GetOwner()->GetComponent<SquareCollider>()))
	{
		GetOwner()->Disable();
		if (next)
		{
			next->GetOwner()->Enable();
			std::cout << "touche" << std::endl;
		}
		else
		{ }
	}
}

void Star::SetNext(Star* nextStar)
{
	next = nextStar;
}
