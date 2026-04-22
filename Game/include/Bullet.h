#pragma once
#include "Core/Component.h"

class Bullet : public Component
{
public:
    Maths::Vector2f velocity;

    void Update(float dt) override
    {
        auto pos = GetOwner()->GetPosition();
        pos = pos + velocity * dt;
        GetOwner()->SetPosition(pos);
    }
};