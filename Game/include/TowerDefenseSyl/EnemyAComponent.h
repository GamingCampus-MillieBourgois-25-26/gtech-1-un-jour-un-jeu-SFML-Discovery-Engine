#pragma once
#include "Core/Component.h"

class EnemyAComponent : public Component
{
public:
	EnemyAComponent(std::vector<Maths::Vector2f> inPath);
	void Update(float _delta_time) override;

	int health = 3;
	float speed = 100;
	int pathIndex = 0;
	std::vector<Maths::Vector2f> path;
};

