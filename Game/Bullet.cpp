#include "Demo/Bullet.h"

void Bullet::Update(const float _delta_time)
{
	GetOwner()->SetPosition({ GetOwner()->GetPosition().x, GetOwner()->GetPosition().y + speedBullet * _delta_time});
	Logger::Log(ELogLevel::Debug, "Une bullet bouge.");
}
