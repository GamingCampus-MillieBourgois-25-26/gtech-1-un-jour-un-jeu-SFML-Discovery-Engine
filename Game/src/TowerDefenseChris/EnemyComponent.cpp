#include "TowerDefenseChris/EnemyComponent.h"
#include "TowerDefenseChris/GameManagerComponent.h"

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

#include <algorithm>
#include <cmath>

std::vector<EnemyComponent*> EnemyComponent::enemies;

EnemyComponent::EnemyComponent()
{
    enemies.push_back(this);
    ResetPath();
}

EnemyComponent::~EnemyComponent()
{
    enemies.erase(std::remove(enemies.begin(), enemies.end(), this), enemies.end());
}

void EnemyComponent::ResetPath()
{
    path = {
        {  32.f, 100.f },
        {  96.f, 100.f },
        { 100.f, 100.f },

        { 100.f, 224.f },
        { 100.f, 288.f },
        { 100.f, 352.f },
        { 100.f, 416.f },
        { 100.f, 420.f },

        { 150.f, 420.f },
        { 230.f, 420.f },

        { 230.f, 416.f },
        { 230.f, 352.f },
        { 230.f, 288.f },
        { 230.f, 224.f },
        { 230.f, 160.f },
        { 230.f,  30.f },

        { 350.f,  30.f },
        { 350.f,  30.f },

        { 350.f, 160.f },
        { 350.f, 224.f },
        { 350.f, 280.f },
        { 350.f, 290.f },

        { 480.f, 290.f },
        { 544.f, 290.f },
        { 608.f, 290.f }
    };

    currentTarget = 0;
}

void EnemyComponent::Spawn()
{
    ResetPath();
    hp = 100.f;
    isDead = false;
    isActive = true;
    GetOwner()->SetPosition(Maths::Vector2f(0.f, 100.f));
}

bool EnemyComponent::IsActive() const
{
    return isActive;
}

void EnemyComponent::Update(float _delta_time)
{
    if (!isActive || isDead)
        return;

    if (currentTarget >= static_cast<int>(path.size()))
    {
        isDead = true;
        isActive = false;
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));

        GameManagerComponent::baseHP--;
        GameManagerComponent::enemiesEscaped++;

        if (GameManagerComponent::baseHP <= 0)
            GameManagerComponent::gameOver = true;

        return;
    }

    Maths::Vector2f position = GetOwner()->GetPosition();
    Maths::Vector2f target = path[currentTarget];

    float dx = target.x - position.x;
    float dy = target.y - position.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 10.f)
    {
        currentTarget++;
        return;
    }

    float dirX = dx / dist;
    float dirY = dy / dist;

    position.x += dirX * speed * _delta_time;
    position.y += dirY * speed * _delta_time;

    GetOwner()->SetPosition(position);
}

void EnemyComponent::TakeDamage(float damage)
{
    if (!isActive || isDead)
        return;

    hp -= damage;

    if (hp <= 0.f)
    {
        isDead = true;
        isActive = false;
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));

        GameManagerComponent::enemiesKilled++;

        if (GameManagerComponent::enemiesKilled >= 10)
            GameManagerComponent::victory = true;
    }
}