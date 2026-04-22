#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/SquareCollider.h"

namespace BulletHell_J {
    class ProjectileJ : public Component {
    public:
        Maths::Vector2f direction;
        float speed = 150.0f;

        void Update(const float _dt) override {
            GetOwner()->SetPosition(GetOwner()->GetPosition() + direction * speed * _dt);

            // Destruction si hors écran (optimisation J1)
            Maths::Vector2f pos = GetOwner()->GetPosition();
            if (pos.x < -50 || pos.x > 650 || pos.y < -50 || pos.y > 650) {
                // Ton moteur semble avoir besoin d'une fonction de destruction 
                // Pour J1, on peut simplement le téléporter très loin si Destroy n'est pas prêt
            }
        }
    };
}