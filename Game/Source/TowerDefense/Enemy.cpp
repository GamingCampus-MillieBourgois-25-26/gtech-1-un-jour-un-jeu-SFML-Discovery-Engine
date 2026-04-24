#include "TowerDefense/Enemy.h"
#include <AssetsModule.h>

TowerDefense::Enemy::Enemy(float _speed, int _health, int _damage, int _coin)
{
	speed = _speed;
	health = _health;
	damage = _damage;
	coin = _coin;
}

void TowerDefense::Enemy::Update(float _delta_time)
{
	float speed = 100 * _delta_time;

	float targetPositionX = GetOwner()->GetPosition().x;
	float targetPositionY = GetOwner()->GetPosition().y;

	MovementPattern(GetOwner(), targetPositionX, targetPositionY, speed);
}

void TowerDefense::Enemy::MovementPattern(GameObject* target, float targetPositionX, float targetPositionY, float speed)
{
	Logger::Log(ELogLevel::Debug, "Points : {}", pointsReached[0]);
	Logger::Log(ELogLevel::Debug, "target : {}", targetPositionX);

	if (pointsReached[0] == false)
	{
		target->SetPosition({ targetPositionX + speed, targetPositionY });
		if (targetPositionX >= 500.f) {
			pointsReached[0] = true;
		}
	}

	else if (pointsReached[1] == false)
	{
		target->SetPosition({ targetPositionX, targetPositionY + speed });
		if (targetPositionY >= 200.f) {
			pointsReached[1] = true;
		}
	}

	else if (pointsReached[2] == false)
	{
		target->SetPosition({ targetPositionX - speed, targetPositionY });
		if (target->GetPosition().x <= 0.f) {
			pointsReached[2] = true;
		}
	}

	else if (pointsReached[3] == false)
	{
		target->SetPosition({ targetPositionX, targetPositionY + speed });
		if (target->GetPosition().y >= 400.f) {
			pointsReached[3] = true;
		}
	}

	else if (pointsReached[4] == false)
	{
		target->SetPosition({ targetPositionX + speed, targetPositionY });
		if (target->GetPosition().x >= 400.f) {
			pointsReached[4] = true;
		}
	}

	else
	{
		Logger::Log(ELogLevel::Debug, "Atteint le chateau --> attaque");
	}
}
