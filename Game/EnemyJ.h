#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "ProjectileJ.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"
#include <numbers>
#include <cmath>

namespace BulletHell_J {
    class EnemyJ : public Component {
    public:
        float timer = 0.f;
        int attackPhase = 0; // Pour alterner les attaques
        Scene* sceneRef = nullptr;
        GameObject* playerRef = nullptr;

        // Fonction utilitaire pour éviter de répéter le code de création
        void SpawnBullet(Maths::Vector2f dir) {
            if (!sceneRef || !playerRef) return;

            GameObject* b = sceneRef->CreateGameObject("Bullet");
            b->SetPosition(GetOwner()->GetPosition());

            ProjectileJ* proj = new ProjectileJ();
            proj->direction = dir;
            proj->targetPlayer = playerRef;
            b->AddComponent(proj);

            SquareCollider* sc = new SquareCollider();
            sc->SetWidth(10.f); sc->SetHeight(10.f);
            b->AddComponent(sc);

            RectangleShapeRenderer* rs = new RectangleShapeRenderer();
            rs->SetSize({ 10.f, 10.f });
            rs->SetColor(sf::Color::Yellow);
            b->AddComponent(rs);
        }

        void FireCircle(int count = 12) {
            const float PI = 3.14159265f;
            for (int i = 0; i < count; ++i) {
                float angle = i * (2.f * PI / count);
                SpawnBullet({ std::cos(angle), std::sin(angle) });
            }
        }

        void FireFan(int count = 5, float spreadDeg = 45.f) {
            if (!playerRef) return;

            // 1. Calculer l'angle vers le joueur
            Maths::Vector2f myPos = GetOwner()->GetPosition();
            Maths::Vector2f targetPos = playerRef->GetPosition();
            float angleToPlayer = std::atan2(targetPos.y - myPos.y, targetPos.x - myPos.x);

            // 2. Convertir l'angle d'éventail en radians
            const float PI = 3.14159265f;
            float spreadRad = spreadDeg * (PI / 180.f);

            float startAngle = angleToPlayer - (spreadRad / 2.f);
            float step = (count > 1) ? spreadRad / (count - 1) : 0;

            for (int i = 0; i < count; ++i) {
                float currentAngle = startAngle + (step * i);
                SpawnBullet({ std::cos(currentAngle), std::sin(currentAngle) });
            }
        }

        void Update(const float _dt) override {
            timer += _dt;

            // On tire toutes les secondes pour bien voir le pattern
            if (timer >= 1.0f) {
                // Paramètres : 7 balles, sur un angle de 45 degrés face au joueur
                FireFan(7, 45.f);

                timer = 0.f;
            }
        }
    };
}