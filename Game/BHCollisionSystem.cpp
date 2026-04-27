#include "BHCollisionSystem.h"
#include "BulletS.h"
#include "EnemyS.h"
#include "PlayerS.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include <cmath>

namespace BulletHell {

    static float Dist(Maths::Vector2f a, Maths::Vector2f b)
    {
        float dx = a.x - b.x, dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void BHCollisionSystem::Update(float dt)
    {
        Scene* scene = GetOwner()->GetScene();
        const auto& gos = scene->GetGameObjects();

        // Récupère le joueur
        PlayerS* player = nullptr;
        Maths::Vector2f playerPos;
        for (auto& go : gos)
        {
            if (go->IsMarkedForDeletion()) continue;
            player = go->GetComponent<PlayerS>();
            if (player) { playerPos = go->GetPosition(); break; }
        }

        for (auto& go : gos)
        {
            if (go->IsMarkedForDeletion()) continue;
            auto* bullet = go->GetComponent<BulletS>();
            if (!bullet) continue;

            Maths::Vector2f bPos = go->GetPosition();

            if (!bullet->isEnemy)
            {
                // Balle joueur vs ennemis
                for (auto& go2 : gos)
                {
                    if (go2->IsMarkedForDeletion()) continue;
                    auto* enemy = go2->GetComponent<EnemyS>();
                    if (!enemy || enemy->IsDead()) continue;

                    float d = Dist(bPos, go2->GetPosition());
                    if (d < bullet->radius + enemy->radius)
                    {
                        enemy->TakeDamage(1.f);
                        go->MarkForDeletion();
                        break;
                    }
                }
            }
            else
            {
                // Balle ennemie vs joueur
                if (player && !player->isDead())
                {
                    float d = Dist(bPos, playerPos);
                    if (d < bullet->radius + player->radius)
                    {
                        player->TakeHit();
                        go->MarkForDeletion();
                    }
                }
            }
        }
    }

}