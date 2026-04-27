#include "pch.h"
#include "Star.h"
#include "Components/SquareCollider.h"
#include "Core/Scene.h"
#include "BulletHellSyl/Enemy.h"
#include "BulletHellSyl/EndGame.h"

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
			next->GetOwner()->Enable();
		else
		{
			const auto& objects = GetOwner()->GetScene()->GetGameObjects();
			for (const auto& object : objects)
			{
				GameObject* obj = object.get();
				if (!obj || obj->IsMarkedForDeletion())
					continue;
				if (obj->GetName() == "Enemy")
				{
					obj->GetComponent<Enemy>()->endGame = true;
				}
				else if (obj->GetName() == "EndDisplay")
				{
					obj->GetComponent<EndGame>()->End(true);
				}
			}
		}
	}
}

void Star::SetNext(Star* nextStar)
{
	next = nextStar;
}
