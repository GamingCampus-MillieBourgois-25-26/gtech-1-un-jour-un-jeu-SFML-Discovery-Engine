#pragma once
#include "Core/Component.h"
#include "InputModule.h"

    class FPlayer : public Component
    {
    private:
        int lives = 3;
        float invincibleTimer = 0.f;
        bool invincible = false;

    public:
        float radius = 15.f;
        void Update(const float _delta_time) override
        {
            if (invincible)
            {
                invincibleTimer -= _delta_time;

                if (invincibleTimer <= 0.f)
                {
                    invincible = false;
                }
            }
            Maths::Vector2<float> position = GetOwner()->GetPosition();

            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                position.x += speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                position.x -= speed * _delta_time;
            }

            if (InputModule::GetKey(sf::Keyboard::Key::Z))
            {
                position.y -= speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::S))
            {
                position.y += speed * _delta_time;
            }

            GetOwner()->SetPosition(position);

            if (InputModule::GetKey(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }
        }
        void TakeDamage()
        {
            if (invincible)
                return; // ignore les hits

            lives--;

            invincible = true;
            invincibleTimer = 0.5f; // 0.5 secondes d’immunité

            if (lives <= 0)
            {
                Engine::GetInstance()->RequestQuit();
            }
        }

        float speed = 100.0f;
    };
