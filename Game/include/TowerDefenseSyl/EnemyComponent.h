#pragma once
#include "Core/Component.h"
#include "TowerDefenseSyl/HQComponent.h"
#include "Maths/vector2.h"
#include "Core/GameObject.h"

class EnemyComponent : public Component
{
public:
	EnemyComponent(std::vector<Maths::Vector2f> inPath, HQComponent* QGComp, int* argent);
	void Update(float _delta_time) override;
	void TakeDamage(int dmg);

	int health = 3;
	float speed = 100;
	int pathIndex = 0;
	int* gold;
	std::vector<Maths::Vector2f> path;
	HQComponent* QG;
};

