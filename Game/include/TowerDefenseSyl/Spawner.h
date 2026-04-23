#pragma once
#include "Core/Component.h"

class Spawner : public Component
{
public:
	Spawner(std::vector<Maths::Vector2f> inPath);
	void Update(float _delta_time) override;
	void Wave1(float _delta_time);

	int wave = 0;
	int count = 0;
	float timer = 0.f;
	float delay = 1.f;
	Maths::Vector2f spawnPoint = { -16.f, 32.f };
	std::vector<Maths::Vector2f> path;
};

