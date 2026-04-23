#include "TowerDefenseChris/EnemyComponent.h"

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

#include <algorithm>
#include <iostream>

std::vector<EnemyComponent*> EnemyComponent::enemies;

EnemyComponent::EnemyComponent()
{
    enemies.push_back(this);
}

EnemyComponent::~EnemyComponent()
{
    enemies.erase(std::remove(enemies.begin(), enemies.end(), this), enemies.end());
}

void EnemyComponent::Update(float _delta_time)
{
    if (isDead)
        return;

    Maths::Vector2f position = GetOwner()->GetPosition();

    if (position.x > 800.f)
    {
        isDead = true;
        enemies.erase(std::remove(enemies.begin(), enemies.end(), this), enemies.end());
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
        return;
    }

    position.x += speed * _delta_time;
    GetOwner()->SetPosition(position);
}

void EnemyComponent::TakeDamage(float damage)
{
    if (isDead)
        return;

    hp -= damage;
    std::cout << "enemy hit, hp = " << hp << "\n";

    if (hp <= 0.f)
    {
        isDead = true;
        enemies.erase(std::remove(enemies.begin(), enemies.end(), this), enemies.end());
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
        std::cout << "enemy mort\n";
    }
}