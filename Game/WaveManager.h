#pragma once
#include "Core/Component.h"
#include <chrono>
#include <cstdint>
#include <random>
#include "Vector2.h"
class WaveManager : public Component
{
public:
	void Update();
	Maths::Vector2f findPlayer(GameObject* player);
	void SpawMechant();
	void CreateWave();






	int RandomInt(const int _min, const int _max)
	{
		thread_local std::mt19937_64 gen(static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

		std::uniform_real_distribution dist(static_cast<float>(_min), static_cast<float>(_max));
		return dist(gen);
	}

};

