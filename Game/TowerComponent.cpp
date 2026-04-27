#include "TowerComponent.h"
#include "EnemyComponent.h"
#include "ProjectileComponent.h"
#include "SpawnQueue.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>

namespace TowerDefence {

    void TowerComponent::Update(float dt)
    {
        fireTimer += dt;
        if (fireTimer < 1.f / fireRate)
            return;

        fireTimer = 0.f;

        EnemyComponent* target = FindClosestEnemy();
        if (target)
        {
            hasPendingShot = true;
            // On capture le nom ICI, avant que Present() soit appelé
            pendingTarget = target->GetOwner()->GetName();
        }
    }

    void TowerComponent::Render(sf::RenderWindow* window)
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();
        float half = cellSize * 0.5f;

        // Corps de la tour (carré bleu centré sur la cellule)
        sf::RectangleShape body(sf::Vector2f(cellSize * 0.8f, cellSize * 0.8f));
        body.setFillColor(color);
        body.setPosition({ pos.x - cellSize * 0.4f, pos.y - cellSize * 0.4f });
        window->draw(body);

        
        sf::CircleShape rangeCircle(range);
        rangeCircle.setFillColor(sf::Color::Transparent);
        rangeCircle.setOutlineColor(sf::Color(100, 180, 255, 50));
        rangeCircle.setOutlineThickness(1.f);
        rangeCircle.setPosition({ pos.x - range, pos.y - range });
        window->draw(rangeCircle);
    }

    void TowerComponent::Present()
    {
        if (!hasPendingShot) return;
        hasPendingShot = false;

        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f towerPos = GetOwner()->GetPosition();
        std::string target = pendingTarget;  
        float   dmg = damage;
        pendingTarget.clear();

        SpawnQueue::Get().Push([scene, towerPos, target, dmg]()
            {
                GameObject* proj = scene->CreateGameObject("Projectile_" + target);
                proj->SetPosition(towerPos);
                auto* pc = proj->CreateComponent<ProjectileComponent>();
                pc->Init(target, dmg, 300.f);
            });
    }

    EnemyComponent* TowerComponent::FindClosestEnemy()
    {
        EnemyComponent* closest = nullptr;
        float minDist = range;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Scene* scene = GetOwner()->GetScene();
        if (!scene) return nullptr;

        for (const auto& go : scene->GetGameObjects())
        {
            auto* enemy = go->GetComponent<EnemyComponent>();
            if (!enemy || enemy->IsDead() || enemy->IsFinished())
                continue;

            Maths::Vector2f ePos = go->GetPosition();
            float dx = ePos.x - pos.x;
            float dy = ePos.y - pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < minDist)
            {
                minDist = dist;
                closest = enemy;
            }
        }
        return closest;
    }

}