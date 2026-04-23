#pragma once

#include "Core/Component.h"
#include <vector>

class TowerComponent : public Component
{
public:
    TowerComponent();
    ~TowerComponent();

    void Update(float _delta_time) override;

    void ActivateAt(float x, float y);
    bool IsActive() const;

    static std::vector<TowerComponent*> towers;

private:
    float range = 120.f;
    float damage = 10.f;
    float cooldown = 0.5f;
    float timer = 0.0f;

    bool isActive = false;
};