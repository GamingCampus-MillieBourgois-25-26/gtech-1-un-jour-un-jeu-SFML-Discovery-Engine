#include "Enemy.h"
#include "BulletComponent.h"
#include "Assets/Texture.h"
#include "Core/GameObject.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Scene.h"
#include <iostream>

Enemy::Enemy()
{
}

void Enemy::Update(const float _delta_time)
{
	timer += _delta_time;
	if (timer >= 2.f)
	{
		timer = -9999.f;
		CreateBullet(GetOwner()->GetPosition());
	}
}

void Enemy::CreateBullet(Maths::Vector2f _position)
{
	GameObject* bullet = GetOwner()->GetScene()->CreateGameObject("bullet");
	bullet->SetPosition(_position);
	bullet->CreateComponent<BulletComponent>();
	SquareCollider* square_collider = bullet->CreateComponent<SquareCollider>();
	square_collider->SetWidth(20.f);
	square_collider->SetHeight(200.f);
	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	bullet->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/BulletHell/laserBlue.png"));
}