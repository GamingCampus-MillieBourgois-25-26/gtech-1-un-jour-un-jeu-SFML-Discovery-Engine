#pragma once
#include "Core/Component.h"

class Bullet : public Component
{
public:
    Maths::Vector2f velocity;
    bool active = false;

    void Activate(const Maths::Vector2f& pos, const Maths::Vector2f& vel)
    {
        active = true;
        velocity = vel;
        GetOwner()->SetPosition(pos);
    }

    void Deactivate()
    {
        active = false;
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
    }

    void Update(float _delta_time) override
    {
        if (!active) return;

        auto pos = GetOwner()->GetPosition();
        pos = pos + velocity * _delta_time;
        GetOwner()->SetPosition(pos);

        // hors écran = recycle
        if (pos.x < -100 || pos.x > 2000 || pos.y < -100 || pos.y > 2000)
        {
            Deactivate();
        }
    }
};