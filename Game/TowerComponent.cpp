#include "TowerComponent.h"
#include "GameObject.h"
#include "EnemyComponent.h"
#include <cmath>
#include <iostream>

void TowerComponent::SetEnemies(const std::vector<GameObject*>* _enemies)
{
    enemies = _enemies;
}

void TowerComponent::Update(float _deltaTime)
{
    if (!enemies)
        return;

    timer += _deltaTime;

    if (timer < fireRate)
        return;

    timer = 0.f;

    Maths::Vector2f towerPos = GetOwner()->GetPosition();

    for (GameObject* enemyGO : *enemies)
    {
        if (!enemyGO->IsEnabled())
            continue;

        Component* base = enemyGO->GetComponent<Component>();

        EnemyComponent* enemy = static_cast<EnemyComponent*>(base);
        if (!enemy || !enemy->IsActive())
            continue;

        Maths::Vector2f enemyPos = enemyGO->GetPosition();

        Maths::Vector2f dir = enemyPos - towerPos;
        float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

        if (dist <= range)
        {
            std::cout << "Enemy in range!" << std::endl;
            break;
        }
    }
}