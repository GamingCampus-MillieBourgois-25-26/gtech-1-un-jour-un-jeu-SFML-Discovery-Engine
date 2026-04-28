#include "ProjectileComponent.h"
#include "TowerDefenseSyl/EnemyTD.h"


ProjectileComponent::ProjectileComponent(GameObject* obj)
{
	target = obj;
	pos = target->GetPosition();
}

void ProjectileComponent::Update(float _delta_time)
{
	Maths::Vector2f direction = pos - GetOwner()->GetPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length < 4.f)
	{
		if (target->IsEnabled())
		{
			EnemyTD* enemy = target->GetComponent<EnemyTD>();
			if (enemy)
				enemy->TakeDamage(damage);
		}
		GetOwner()->MarkForDeletion();
	}
	else
	{
		if (length > 0.f)
			direction /= length;
		Maths::Vector2f displacement = direction * speed * _delta_time;
		GetOwner()->SetPosition(GetOwner()->GetPosition() + displacement);
	}
}