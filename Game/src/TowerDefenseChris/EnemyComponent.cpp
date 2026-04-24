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
    {  92.f, 160.f },
    { 156.f, 160.f },
    { 160.f, 160.f },

    { 160.f, 284.f },
    { 160.f, 348.f },
    { 160.f, 412.f },
    { 160.f, 476.f },
    { 160.f, 480.f },

    { 210.f, 480.f },
    { 290.f, 480.f },

    { 290.f, 476.f },
    { 290.f, 412.f },
    { 290.f, 348.f },
    { 290.f, 284.f },
    { 290.f, 220.f },
    { 290.f,  90.f },

    { 410.f,  90.f },
    { 410.f,  90.f },

    { 410.f, 220.f },
    { 410.f, 284.f },
    { 410.f, 340.f },
    { 410.f, 350.f },

    { 540.f, 350.f },
    { 604.f, 350.f },
    { 668.f, 350.f }
    };
 

    currentTarget = 0;
}

void EnemyComponent::Spawn()
{
    ResetPath();
    hp = 100.f;
    isDead = false;
    isActive = true;
    GetOwner()->SetPosition(Maths::Vector2f(32.f, 160.f));
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