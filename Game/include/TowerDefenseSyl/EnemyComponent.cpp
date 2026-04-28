#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(std::vector<Maths::Vector2f> inPath, HQComponent* QGComp, int* argent)
{
	path = inPath;
    QG = QGComp;
    gold = argent;
}

void EnemyComponent::Update(float _delta_time)
{
    if (pathIndex >= path.size())
    {
        QG->TakeDamage();
        GetOwner()->MarkForDeletion();
        return;
    }
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

void EnemyComponent::TakeDamage(int dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        GetOwner()->Disable();
        *gold += 1;
    }
}