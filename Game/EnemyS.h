#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    enum class EnemyPattern { Line, Spiral, Burst };

    class EnemyS : public Component
    {
    public:
        float         hp = 3.f;
        float         radius = 18.f;
        int           scoreValue = 100;
        EnemyPattern  pattern = EnemyPattern::Line;

        // Mouvement
        Maths::Vector2f velocity = { 0.f, 60.f };

        bool IsDead()   const { return dead; }
        void TakeDamage(float dmg);

        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;
        void Present() override;

    private:
        float shootTimer = 0.f;
        float shootRate = 1.8f;
        float angle = 0.f;   // pour la spirale
        bool  dead = false;
        bool  done = false;

        void ShootLine();
        void ShootSpiral(float dt);
        void ShootBurst();
    };

}