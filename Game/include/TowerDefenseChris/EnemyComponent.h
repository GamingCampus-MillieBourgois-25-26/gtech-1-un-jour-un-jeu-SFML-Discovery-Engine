#pragma once

#include "Core/Component.h"
#include <vector>

class EnemyComponent : public Component
{
public:
    EnemyComponent();
    ~EnemyComponent();

    void Update(float _delta_time) override;
    void TakeDamage(float damage);

    static std::vector<EnemyComponent*> enemies;

private:
    float speed = 100.f;
    float hp = 100.f;
    bool isDead = false;
};