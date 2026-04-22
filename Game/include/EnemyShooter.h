#pragma once

#include "Core/Component.h"
#include "Bullet.h"
#include "Patterns.h"
class EnemyShooter : public Component
{
public:
    float timer = 0.f;

    void Update(float dt) override
    {
        timer += dt;

        if (timer > 1.f)
        {
            ShootCircle();
            timer = 0.f;
        }
    }

private:
    void ShootCircle()
    {
        GameObject* owner = GetOwner();

        for (int i = 0; i < 36; i++)
        {
            float angle = i * 10.f;
            float rad = angle * 3.14159f / 180.f;

            GameObject* bullet = owner->GetScene()->CreateGameObject("Bullet");

            bullet->SetPosition(owner->GetPosition());

            auto b = bullet->CreateComponent<Bullet>();

            b->velocity = Maths::Vector2f(
                std::cos(rad) * 200.f,
                std::sin(rad) * 200.f
            );
        }
    }
};