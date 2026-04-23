#include "ProjectileComponent.h"


ProjectileComponent::ProjectileComponent(Maths::Vector2f position, Maths::Vector2f inTarget)
{
	GetOwner()->SetPosition(position);
	target = inTarget;
}

void ProjectileComponent::Update(float _delta_time)
{
	GetOwner()->SetPosition(GetOwner()->GetPosition() * _delta_time * speed * target);
	float distance = std::sqrt(target.x * target.x + target.y * target.y);
	if (distance <= 2.f)
	{
		GetOwner()->MarkForDeletion();
	}
}