#pragma once
#include "Core/Component.h"
#include "EnemyComponent.h"
#include <vector>
#include <queue>

namespace TowerDefence {

    class WaveManager : public Component {

    public:

        void SetConfig(const std::vector<Maths::Vector2i>& path, float cellSize);
        void Start()          override;
        void Update(float dt) override;
        void Present()        override; // ← spawn ici, pas dans Update

        int   maxWaves = 3;
        int   enemiesPerWave = 5;
        float spawnInterval = 1.5f;
        float waveCooldown = 5.f;

        int  GetCurrentWave() const { return currentWave; }
        bool IsAllWavesDone() const { return allWavesDone; }

    private:

        void SpawnEnemy();

        std::vector<Maths::Vector2i> enemyPath;
        float cellSize = 50.f;

        int   currentWave = 1;
        int   enemiesSpawned = 0;
        float spawnTimer = 0.f;
        float waveCooldownTimer = 0.f;
        bool  wavePending = false;
        bool  allWavesDone = false;
        bool  started = false;

        int   pendingSpawns = 0; // ← file d'attente de spawns
    };

}