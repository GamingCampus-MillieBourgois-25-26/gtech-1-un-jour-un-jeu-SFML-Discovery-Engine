#include "TowerAComponent.h"
#include "ProjectileComponent.h"
#include "Components/SpriteRenderer.h"
#include "Modules/AssetsModule.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <iostream>

TowerAComponent::TowerAComponent()
{

}

void TowerAComponent::Update(float _delta_time)
{
    atkSpeed += _delta_time;
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

void TowerAComponent::shot(GameObject* obj)
{
    std::cout << "shot" << std::endl;
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    GameObject* projectile = GetOwner()->GetScene()->CreateGameObject("projectile");
    projectile->CreateComponent<ProjectileComponent>(GetOwner()->GetPosition(), obj->GetPosition());
    projectile->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/bullet.png"));
}

GameObject* TowerAComponent::FindTarget()
{
    GameObject* owner = GetOwner();
    const auto& objects = owner->GetScene()->GetGameObjects();
    for (const auto& object : objects)
    {
        GameObject* obj = object.get();
        if (!obj || obj->IsMarkedForDeletion())
            continue;
        /*if (obj->GetName().find("Enemy") == std::string::npos)
            continue;*/
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