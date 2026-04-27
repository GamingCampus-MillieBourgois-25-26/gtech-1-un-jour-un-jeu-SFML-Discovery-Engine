#include "Enemy.h"
#include "BulletComponent.h"
#include "Assets/Texture.h"
#include "Core/GameObject.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include <iostream>

Enemy::Enemy()
{
}

void Enemy::Update(const float _delta_time)
{
	timer += _delta_time;
	if (timer >= 0.1f && !endGame)
	{
		timer = 0.f;
		CreateBullet(GetOwner()->GetPosition());
	}
}

void Enemy::CreateBullet(Maths::Vector2f _position)
{
	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	GameObject* bullet = GetOwner()->GetScene()->CreateGameObject("bullet");
	bullet->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/BulletHell/bullet.png"));
	bullet->CreateComponent<BulletComponent>();
	SquareCollider* collider = bullet->CreateComponent<SquareCollider>();
	collider->SetHeight({ 25.f });
	collider->SetWidth({ 25.f });
	collider->SetPivot({ 12.5f, 12.5f });
	bullet->SetPosition(_position);
	bullet->SetScale({ 0.7f, 0.7f });
	/*RectangleShapeRenderer* shape = bullet->CreateComponent<RectangleShapeRenderer>();
	shape->SetColor(sf::Color::Blue);
	shape->SetSize({ 25, 25 });*/
	//shape->SetPivot({ 10.f, 10.f });
}