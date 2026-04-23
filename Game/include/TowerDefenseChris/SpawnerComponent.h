#pragma once

#include "Core/Component.h"

class SpawnerComponent : public Component
{
public:
    void Update(float _delta_time) override;

private:
    float timer = 0.f;
};