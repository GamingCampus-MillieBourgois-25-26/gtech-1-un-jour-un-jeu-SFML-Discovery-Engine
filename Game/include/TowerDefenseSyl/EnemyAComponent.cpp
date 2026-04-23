#include "EnemyAComponent.h"

EnemyAComponent::EnemyAComponent(std::vector<Maths::Vector2f> inPath)
{
	path = inPath;
}

void EnemyAComponent::Update(float _delta_time)
{
    if (pathIndex >= path.size())
        return;
    Maths::Vector2f direction = path[pathIndex] - GetOwner()->GetPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 1.5f)
        pathIndex++;
    else
    {
        direction /= distance;
        GetOwner()->SetPosition(GetOwner()->GetPosition() += direction * speed * _delta_time);
    }
}