#include "SmallBullet.h"
#include "Core/GameObject.h"
#include <cmath>
#include <random>

SmallBullet::SmallBullet()
{
    direction = randomDirection();
}

void SmallBullet::Update(float _delta_time)
{
    Maths::Vector2f position = GetOwner()->GetPosition();
    position += direction * speed * _delta_time;
    GetOwner()->SetPosition(position);
}

Maths::Vector2f SmallBullet::randomDirection()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.f, 2.f * 3.14159265f);

    float angle = dist(gen);

    return Maths::Vector2f(std::cos(angle), std::sin(angle));
}