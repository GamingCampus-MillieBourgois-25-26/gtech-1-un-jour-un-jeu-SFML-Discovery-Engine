#include "WaveManagerComponent.h"
#include "GameObject.h"
#include "Engine.h"
#include "Scene.h"

#include "TDScene.h"

void WaveManagerComponent::Update(float _deltaTime)
{
    if (enemiesSpawned >= enemiesToSpawn)
        return;

    spawnTimer += _deltaTime;

    if (spawnTimer >= spawnDelay)
    {
        spawnTimer = 0.f;

        SpawnEnemy();
        enemiesSpawned++;
    }
}