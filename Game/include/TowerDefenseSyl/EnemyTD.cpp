#include "EnemyTD.h"

EnemyTD::EnemyTD(std::vector<Maths::Vector2f> inPath, HQComponent* QGComp, int* argent)
{
	path = inPath;
    QG = QGComp;
    gold = argent;
}

void EnemyTD::Update(float _delta_time)
{
    if (pathIndex >= path.size())
    {
        QG->TakeDamage();
        GetOwner()->MarkForDeletion();
        GetOwner()->Disable();
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

void EnemyTD::TakeDamage(int dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        *gold += 1;
        GetOwner()->MarkForDeletion();
        GetOwner()->Disable();
    }
}