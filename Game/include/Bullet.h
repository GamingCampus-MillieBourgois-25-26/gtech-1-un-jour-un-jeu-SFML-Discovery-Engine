#pragma once
#include "Core/Component.h"

class Bullet : public Component
{
public:
    Maths::Vector2f velocity;

    void Update(float _delta_time) override
    {
        auto pos = GetOwner()->GetPosition();
        pos = pos + velocity * _delta_time;
        GetOwner()->SetPosition(pos);
    }
};