#pragma once
#include <cmath>
#include "Core/GameObject.h"
#include "Bullet.h"

namespace Patterns
{
    inline void ShootCircle(GameObject* owner)
    {
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

    inline void ShootSpiral(GameObject* owner)
    {
        static float baseAngle = 0.f;

        for (int i = 0; i < 8; i++)
        {
            float angle = baseAngle + i * 20.f;
            float rad = angle * 3.14159f / 180.f;

            GameObject* bullet = owner->GetScene()->CreateGameObject("Bullet");
            bullet->SetPosition(owner->GetPosition());

            auto b = bullet->CreateComponent<Bullet>();

            b->velocity = Maths::Vector2f(
                std::cos(rad) * 200.f,
                std::sin(rad) * 200.f
            );
        }

        baseAngle += 5.f;
    }

    inline void ShootWave(GameObject* owner)
    {
        static float t = 0.f;

        for (int i = 0; i < 10; i++)
        {
            float offsetY = (i - 5) * 20.f;

            float angle = std::sin(t + i * 0.5f) * 45.f;
            float rad = angle * 3.14159f / 180.f;

            GameObject* bullet = owner->GetScene()->CreateGameObject("Bullet");
            bullet->SetPosition(owner->GetPosition() + Maths::Vector2f(0, offsetY));

            auto b = bullet->CreateComponent<Bullet>();

            b->velocity = Maths::Vector2f(
                std::cos(rad) * 250.f,
                std::sin(rad) * 100.f
            );
        }

        t += 0.1f;
    }

    inline void ShootLaser(GameObject* owner)
    {
        float angle = 0.f;
        float rad = angle * 3.14159f / 180.f;

        for (int i = 0; i < 20; i++)
        {
            GameObject* bullet = owner->GetScene()->CreateGameObject("Bullet");

            bullet->SetPosition(owner->GetPosition() + Maths::Vector2f(
                std::cos(rad) * i * 10.f,
                std::sin(rad) * i * 10.f
            ));

            auto b = bullet->CreateComponent<Bullet>();

            b->velocity = Maths::Vector2f(
                std::cos(rad) * 300.f,
                std::sin(rad) * 300.f
            );
        }
    }
}