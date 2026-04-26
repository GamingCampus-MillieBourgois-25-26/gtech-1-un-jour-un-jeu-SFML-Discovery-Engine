#include "BHWaveManager.h"
#include "BHGameState.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"

namespace BulletHell {

    void BHWaveManager::BuildWaves()
    {
        // Vague 1 — ennemis en ligne
        WaveData w1;
        for (int i = 0; i < 5; i++)
            w1.enemies.push_back({ { 150.f + i * 150.f, -40.f },
                                   EnemyPattern::Line, { 0.f, 50.f }, 3.f });
        waves.push_back(w1);

        // Vague 2 — spirale + ligne
        WaveData w2;
        w2.enemies.push_back({ { 500.f, -40.f }, EnemyPattern::Spiral, { 0.f, 35.f }, 6.f });
        for (int i = 0; i < 4; i++)
            w2.enemies.push_back({ { 100.f + i * 200.f, -40.f },
                                   EnemyPattern::Line, { 0.f, 55.f }, 3.f });
        waves.push_back(w2);

        // Vague 3 — burst + spirale
        WaveData w3;
        for (int i = 0; i < 3; i++)
            w3.enemies.push_back({ { 200.f + i * 300.f, -40.f },
                                   EnemyPattern::Burst, { 0.f, 40.f }, 5.f });
        w3.enemies.push_back({ { 500.f, -40.f }, EnemyPattern::Spiral, { 0.f, 30.f }, 8.f });
        waves.push_back(w3);
    }

    void BHWaveManager::Start()
    {
        BuildWaves();
        BHGameState::Get().wave = 1;
    }

    bool BHWaveManager::AllEnemiesDead() const
    {
        Scene* scene = GetOwner()->GetScene();
        for (const auto& go : scene->GetGameObjects())
        {
            if (go->IsMarkedForDeletion()) continue;
            auto* e = go->GetComponent<EnemyS>();
            if (e && !e->IsDead()) return false;
        }
        return true;
    }

    void BHWaveManager::Update(float dt)
    {
        if (done || BHGameState::Get().gameOver) return;

        // Entre deux vagues
        if (waitingNext)
        {
            if (!AllEnemiesDead()) return;
            waveTimer += dt;
            if (waveTimer < waveDelay) return;

            waveTimer = 0.f;
            waitingNext = false;
            currentWave++;
            spawnIndex = 0;
            spawnTimer = 0.f;
            BHGameState::Get().wave = currentWave + 1;
        }

        if (currentWave >= static_cast<int>(waves.size()))
        {
            if (AllEnemiesDead())
            {
                done = true;
                BHGameState::Get().victory = true;
            }
            return;
        }

        // Spawn des ennemis de la vague courante
        const WaveData& wave = waves[currentWave];
        if (spawnIndex < static_cast<int>(wave.enemies.size()))
        {
            spawnTimer += dt;
            if (spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.f;
                pendingSpawn = spawnIndex;
                spawnIndex++;
            }
        }
        else if (spawnIndex >= static_cast<int>(wave.enemies.size()))
        {
            // Tous spawnés, on attend qu'ils meurent
            if (currentWave < static_cast<int>(waves.size()) - 1)
                waitingNext = true;
            else if (AllEnemiesDead())
            {
                done = true;
                BHGameState::Get().victory = true;
            }
            spawnIndex = INT_MAX; // évite de re-rentrer
        }
    }

    void BHWaveManager::Present()
    {
        if (pendingSpawn < 0) return;
        int idx = pendingSpawn;
        pendingSpawn = -1;

        if (currentWave >= static_cast<int>(waves.size())) return;
        const WaveData& wave = waves[currentWave];
        if (idx >= static_cast<int>(wave.enemies.size())) return;

        const EnemySpawnInfo& info = wave.enemies[idx];
        Scene* scene = GetOwner()->GetScene();

        static int eid = 0;
        GameObject* obj = scene->CreateGameObject("Enemy_" + std::to_string(eid++));
        obj->SetPosition(info.position);

        auto* e = obj->CreateComponent<EnemyS>();
        e->pattern = info.pattern;
        e->velocity = info.velocity;
        e->hp = info.hp;
    }

}