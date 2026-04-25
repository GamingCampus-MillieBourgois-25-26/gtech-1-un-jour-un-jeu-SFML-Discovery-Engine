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
        else if (currentWave >= maxWaves)
        {
            // Toutes les vagues spawned — attend que tous les ennemis soient morts
            allWavesDone = true;
        }
        else
        {
            wavePending = true;
            waveCooldownTimer = waveCooldown;
        }
    }

    void WaveManager::Present()
    {
        // Vérifie la victoire : toutes vagues terminées + aucun ennemi vivant
        if (allWavesDone && !GameState::Get().gameOver && !GameState::Get().victory)
        {
            Scene* scene = GetOwner()->GetScene();
            bool anyAlive = false;
            for (const auto& go : scene->GetGameObjects())
            {
                auto* enemy = go->GetComponent<EnemyComponent>();
                if (enemy && !enemy->IsDead() && !enemy->IsFinished())
                {
                    anyAlive = true;
                    break;
                }
            }
            if (!anyAlive)
                GameState::Get().victory = true;
        }

        // Spawn des ennemis en attente
        while (pendingSpawns > 0)
        {
            pendingSpawns--;
            Scene* scene = GetOwner()->GetScene();
            auto        path = enemyPath;
            float       cs = cellSize;
            int         wave = currentWave;
            static int  enemyId = 0;
            std::string name = "Enemy_" + std::to_string(enemyId++);

            SpawnQueue::Get().Push([scene, path, cs, name, wave]()
                {
                    GameObject* obj = scene->CreateGameObject(name);
                    auto* enemy = obj->CreateComponent<EnemyComponent>();
                    enemy->SetPath(path, cs);

                    float hpScale = 1.f + (wave - 1) * 0.75f;
                    float speedScale = 1.f + (wave - 1) * 0.2f;

                    enemy->maxHP = 100.f * hpScale;
                    enemy->hp = enemy->maxHP;
                    enemy->speed = 120.f * speedScale;
                    enemy->reward = 25 * wave;
                });
        }
    }
 void WaveManager::SpawnEnemy(){}
}