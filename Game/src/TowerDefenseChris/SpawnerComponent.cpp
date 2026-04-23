#include "TowerDefenseChris/SpawnerComponent.h"
#include "TowerDefenseChris/EnemyComponent.h"
#include "TowerDefenseChris/GameManagerComponent.h"

void SpawnerComponent::Update(float _delta_time)
{
    if (GameManagerComponent::gameOver || GameManagerComponent::victory)
        return;

    timer += _delta_time;

    if (timer < 2.0f)
        return;

    timer = 0.f;

    for (EnemyComponent* enemy : EnemyComponent::enemies)
    {
        if (enemy != nullptr && !enemy->IsActive())
        {
            enemy->Spawn();
            break;
        }
    }
}