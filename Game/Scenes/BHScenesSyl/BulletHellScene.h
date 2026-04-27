#pragma once

#include "BulletHellSyl/Player.h"
#include "BulletHellSyl/Enemy.h"
#include "BulletHellSyl/BulletComponent.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"
#include <vector>

class BulletHellScene final : public Scene
{
public:
	BulletHellScene() : Scene("BulletHellScene")
	{
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();
		InputModule* input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();

		// Textures
		Texture* playerTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/playerShip.png");
		Texture* ennemyTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/ufoRed.png");
		Texture* bulletTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/bullet.png");

		// GameObjects
		GameObject* player = CreateGameObject("Player");
		SpriteRenderer* tex = player->CreateComponent<SpriteRenderer>(playerTex);
		player->CreateComponent<Player>();
		SquareCollider* collider = player->CreateComponent<SquareCollider>();
		collider->SetWidth({90.f});
		collider->SetHeight({60.f});
		collider->SetPivot({ 45.f, 30.f });
		player->SetPosition({ 250.f, 400.f });
		player->SetScale({ 0.3f, 0.3f });

		GameObject* enemy = CreateGameObject("Enemy");
		enemy->CreateComponent<SpriteRenderer>(ennemyTex);
		enemy->CreateComponent<Enemy>();
		enemy->SetScale({ 0.5f, 0.5f });
		enemy->SetPosition({ (float)window_size.x / 2.f, (float)window_size.y / 2.f });
	}
};