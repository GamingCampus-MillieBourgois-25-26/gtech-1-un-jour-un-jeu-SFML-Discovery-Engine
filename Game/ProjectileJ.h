#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/SquareCollider.h"
#include "PlayerJ.h"

namespace BulletHell_J {
    class ProjectileJ : public Component {
    public:
        Maths::Vector2f direction;
        float speed = 300.0f;
        GameObject* targetPlayer = nullptr;

        void Update(const float _dt) override {
            if (!targetPlayer) return;

            GetOwner()->SetPosition(GetOwner()->GetPosition() + direction * speed * _dt);

            if (targetPlayer) {
                // Recherche manuelle du collider du joueur
                SquareCollider* pCol = nullptr;
                for (Component* c : targetPlayer->GetComponents()) {
                    pCol = dynamic_cast<SquareCollider*>(c);
                    if (pCol) break;
                }

                // Recherche de mon propre collider
                SquareCollider* myCol = nullptr;
                for (Component* c : GetOwner()->GetComponents()) {
                    myCol = dynamic_cast<SquareCollider*>(c);
                    if (myCol) break;
                }

                if (pCol && myCol && SquareCollider::IsColliding(*myCol, *pCol)) {
                    for (Component* c : targetPlayer->GetComponents()) {
                        PlayerJ* pJ = dynamic_cast<PlayerJ*>(c);
                        if (pJ) {
                            pJ->TakeDamage();
                            GetOwner()->SetPosition({ -1000.f, -1000.f }); // On "détruit"
                            break;
                        }
                    }
                }
            }
        }
    };
}