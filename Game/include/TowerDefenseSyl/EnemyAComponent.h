#pragma once
#include "Core/Component.h"
#include "TowerDefenseSyl/HQComponent.h"
#include "Maths/vector2.h"
#include "Core/GameObject.h"

class EnemyAComponent : public Component
{
public:
	EnemyAComponent(std::vector<Maths::Vector2f> inPath, HQComponent* QGComp);
	void Update(float _delta_time) override;
	void InflictDamage(int dmg);

	int health = 3;
	float speed = 100;
	int pathIndex = 0;
	std::vector<Maths::Vector2f> path;
	HQComponent* QG;
};

