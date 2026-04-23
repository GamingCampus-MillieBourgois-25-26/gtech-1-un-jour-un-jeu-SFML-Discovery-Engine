#include "TowerDefenseChris/TowerComponent.h"
#include "TowerDefenseChris/EnemyComponent.h"

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

#include <cmath>
#include <iostream>

void TowerComponent::Update(float _delta_time)
{
    timer += _delta_time;

    if (timer < cooldown)
        return;

    Maths::Vector2f myPos = GetOwner()->GetPosition();

    EnemyComponent* target = nullptr;
    float bestDist = range;

    for (EnemyComponent* enemy : EnemyComponent::enemies)
    {
        if (enemy == nullptr)
            continue;

        if (enemy->GetOwner() == nullptr)
            continue;

        Maths::Vector2f enemyPos = enemy->GetOwner()->GetPosition();

        float dx = enemyPos.x - myPos.x;
        float dy = enemyPos.y - myPos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= bestDist)
        {
            bestDist = dist;
            target = enemy;
        }
    }

    if (target != nullptr)
    {
        std::cout << "tour attaque\n";
        target->TakeDamage(damage);
        timer = 0.0f;
    }
}