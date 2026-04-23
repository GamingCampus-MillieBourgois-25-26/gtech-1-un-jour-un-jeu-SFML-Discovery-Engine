#pragma once

#include "Core/Component.h"

class TowerComponent : public Component
{
public:
    void Update(float _delta_time) override;

private:
    float range = 200.f;
    float damage = 50.f;
    float cooldown = 0.2f;
    float timer = 0.0f;
};