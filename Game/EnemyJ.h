#pragma once
#include "Core/Component.h"
#include <numbers>
#include <cmath>

namespace BulletHell_J {
    class EnemyJ : public Component {
    public:
        float circleTimer = 0.f;

        void Update(const float _dt) override {
            circleTimer += _dt;

            if (circleTimer >= 1.5f) {
                FireCircle();
                circleTimer = 0.f;
            }
        }

        void FireCircle() {
            const int count = 8;
            // Utilisation de std::numbers::pi_v
            const float PI = std::numbers::pi_v<float>;

            for (int i = 0; i < count; ++i) {
                float angle = i * (2.f * PI / count);
                Maths::Vector2f dir(std::cos(angle), std::sin(angle));
                // Ici tu instancieras tes projectiles
            }
        }
    };
}