#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "BHGameState.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    class PlayerS : public Component
    {
    public:
        float speed = 280.f;
        float fireRate = 0.12f;
        int   maxLives = 3;
        int   lives = 3;
        float radius = 14.f;

        bool  isDead()    const { return lives <= 0; }
        void  TakeHit();

        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;

    private:
        float fireTimer = 0.f;
        float hitCooldown = 0.f;   // invincibilité brève après un hit

        void HandleMovement(float dt);
        void HandleShooting(float dt);
        void Shoot();
    };

}