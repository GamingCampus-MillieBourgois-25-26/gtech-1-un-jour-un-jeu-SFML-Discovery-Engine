#include "WaveManager.h"
#include "SpawnQueue.h"
#include "GameState.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"

namespace TowerDefence {

    void WaveManager::SetConfig(const std::vector<Maths::Vector2i>& path, float cs)
    {
        enemyPath = path;
        cellSize = cs;
    }

    void WaveManager::Start()
    {
        maxWaves = GameState::Get().maxWaves;
        spawnTimer = spawnInterval;
        started = true;
    }

    void WaveManager::Update(float dt)
    {
        if (!started || allWavesDone) return;
        if (GameState::Get().gameOver) return;

        GameState::Get().currentWave = currentWave;

        if (wavePending)
        {
            waveCooldownTimer -= dt;
            if (waveCooldownTimer <= 0.f)
            {
                wavePending = false;
                enemiesSpawned = 0;
                spawnTimer = spawnInterval;
                currentWave++;
            }
            return;
        }

        if (enemiesSpawned < enemiesPerWave)
        {
            spawnTimer += dt;
            if (spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.f;
                pendingSpawns++;
                enemiesSpawned++;
            }
        }
        else
        {
            if (currentWave >= maxWaves)
            {
                allWavesDone = true;
                // Victoire seulement si le joueur est encore en vie
                if (!GameState::Get().gameOver)
                    GameState::Get().victory = true;
            }
            else
            {
                wavePending = true;
                waveCooldownTimer = waveCooldown;
            }
        }
    }

    void WaveManager::Present()
    {
        while (pendingSpawns > 0)
        {
            pendingSpawns--;
            Scene* scene = GetOwner()->GetScene();
            auto        path = enemyPath;
            float       cs = cellSize;

            static int enemyId = 0;
            std::string name = "Enemy_" + std::to_string(enemyId++);

            SpawnQueue::Get().Push([scene, path, cs, name]()
                {
                    GameObject* obj = scene->CreateGameObject(name);
                    auto* enemy = obj->CreateComponent<EnemyComponent>();
                    enemy->SetPath(path, cs);
                });
        }
    }

    void WaveManager::SpawnEnemy()
    {
    }

}