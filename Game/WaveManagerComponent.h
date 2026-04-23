#pragma once

#include "Core/Component.h"

class WaveManagerComponent : public Component
{
public:
    void Update(float _deltaTime) override;

private:
    float spawnTimer = 0.f;
    float spawnDelay = 1.f;

    int enemiesToSpawn = 5;
    int enemiesSpawned = 0;

    void SpawnEnemy();
};