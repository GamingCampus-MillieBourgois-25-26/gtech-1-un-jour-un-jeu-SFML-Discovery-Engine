#include "ProjectileComponent.h"


ProjectileComponent::ProjectileComponent(Maths::Vector2f inTarget)
{
	target = inTarget;
}

void ProjectileComponent::Update(float _delta_time)
{
	//Maths::Vector2f direction = target - GetOwner()->GetPosition();
	//float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//if (distance >= 2.f)
	//{
	//	GetOwner()->SetPosition(GetOwner()->GetPosition() * _delta_time * speed * target);
	//	//GetOwner()->MarkForDeletion();
	//}
	Maths::Vector2f direction = target - GetOwner()->GetPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 0) {
		direction /= length; // Normalisation
	}
	Maths::Vector2f displacement = direction * speed * _delta_time;
	GetOwner()->SetPosition(displacement);
}