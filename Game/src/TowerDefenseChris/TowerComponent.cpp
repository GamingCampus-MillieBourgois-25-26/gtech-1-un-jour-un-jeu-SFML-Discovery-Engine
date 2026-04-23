#include "TowerDefenseChris/TowerComponent.h"
#include "TowerDefenseChris/EnemyComponent.h"

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

#include <algorithm>
#include <cmath>

std::vector<TowerComponent*> TowerComponent::towers;

TowerComponent::TowerComponent()
{
    towers.push_back(this);
}

TowerComponent::~TowerComponent()
{
    towers.erase(std::remove(towers.begin(), towers.end(), this), towers.end());
}

void TowerComponent::ActivateAt(float x, float y)
{
    isActive = true;
    timer = 0.f;
    GetOwner()->SetPosition(Maths::Vector2f(x, y));
}

bool TowerComponent::IsActive() const
{
    return isActive;
}

void TowerComponent::Update(float _delta_time)
{
    if (!isActive)
        return;

    timer += _delta_time;

    if (timer < cooldown)
        return;

    Maths::Vector2f myPos = GetOwner()->GetPosition();

    EnemyComponent* target = nullptr;
    float bestDist = range;

    for (EnemyComponent* enemy : EnemyComponent::enemies)
    {
        if (enemy == nullptr || !enemy->IsActive())
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
        target->TakeDamage(damage);
        timer = 0.0f;
    }
}