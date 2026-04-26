#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "EnemyS.h"
#include <vector>

namespace BulletHell {

    struct EnemySpawnInfo
    {
        Maths::Vector2f  position;
        EnemyPattern     pattern;
        Maths::Vector2f  velocity;
        float            hp;
    };

    struct WaveData
    {
        std::vector<EnemySpawnInfo> enemies;
    };

    class BHWaveManager : public Component
    {
    public:
        void Start()          override;
        void Update(float dt) override;
        void Present()        override;

    private:
        void BuildWaves();
        void SpawnNext();
        bool AllEnemiesDead() const;

        std::vector<WaveData> waves;
        int   currentWave = 0;
        int   spawnIndex = 0;
        float spawnTimer = 0.f;
        float spawnInterval = 0.8f;
        float waveDelay = 3.f;
        float waveTimer = 0.f;
        bool  waitingNext = false;
        bool  done = false;

        int   pendingSpawn = -1;  // index dans waves[currentWave] à spawner
    };

}