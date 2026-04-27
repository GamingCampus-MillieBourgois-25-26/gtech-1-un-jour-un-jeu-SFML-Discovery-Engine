#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <vector>

class EnemyComponent : public Component
{
public:
    EnemyComponent();
    ~EnemyComponent();

    void Update(float _delta_time) override;
    void TakeDamage(float damage);

    void Spawn();
    bool IsActive() const;

    static std::vector<EnemyComponent*> enemies;

private:
    void ResetPath();

private:
    float speed = 50.f;
    float hp = 100.f;
    bool isDead = true;
    bool isActive = false;

    std::vector<Maths::Vector2f> path;
    int currentTarget = 0;
};