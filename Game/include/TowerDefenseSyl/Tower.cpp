#include "TowerDefenseSyl/Tower.h"

Tower::Tower(Type towerType)
{
    type = towerType;
    if (type == Type::A)
    {
        damage = 1;
        atkSpeed = 1.6f;
        reload = atkSpeed;
        range = 150.f;
    }
    else
    {
        damage = 1;
        atkSpeed = 0.5f;
        reload = atkSpeed;
        range = 130.f;
    }
}

void Tower::Update(float _delta_time)
{
    reload += _delta_time;
    GameObject* obj = FindTarget();
    if (obj)
    {
        if (reload >= atkSpeed)
        {
            reload = 0.f;
            shot(obj);
        }
    }
}

void Tower::shot(GameObject* obj)
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("projectile");
    projectile->SetPosition(GetOwner()->GetPosition());
    projectile->SetScale({ 0.25f, 0.25f });
    projectile->CreateComponent<ProjectileComponent>(obj);
    projectile->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/bullet.png"));
}

GameObject* Tower::FindTarget()
{
    GameObject* owner = GetOwner();
    const auto& objects = owner->GetScene()->GetGameObjects();
    for (const auto& object : objects)
    {
        GameObject* obj = object.get();
        if (!obj || obj->IsMarkedForDeletion())
            continue;
        if (obj->GetName().find("enemy") == std::string::npos && !obj->IsMarkedForDeletion())
            continue;
        Maths::Vector2f dir = obj->GetPosition() - owner->GetPosition();
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (distance <= range)
        {
            //setRotation
            return obj;
        }
    }
    return nullptr;
}