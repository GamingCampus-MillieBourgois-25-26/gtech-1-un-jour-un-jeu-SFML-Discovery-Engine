#pragma once
#include "Core/Component.h"
#include "InputModule.h"

class Enemy : public Component
{
public:
    Enemy() = default;
    ~Enemy() override = default;

    void Start() override
    {
        velocity = Maths::Vector2f(150.f, 120.f); // vitesse initiale
    }

    void Update(const float _delta_time) override
    {
		Maths::Vector2<float> position = GetOwner()->GetPosition();

        // Déplacement
        position.x += velocity.x * _delta_time;
        position.y += velocity.y * _delta_time;

        Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

        // Taille de l'objet 
        const float size = 20.f;

        if (position.x <= 0.f || position.x + size >= window_size.x)
        {
            velocity.x *= -1.f;
        }

        if (position.y <= 0.f || position.y + size >= window_size.y)
        {
            velocity.y *= -1.f;
        }

		GetOwner()->SetPosition(position);
    }

private:
    Maths::Vector2f velocity;
};