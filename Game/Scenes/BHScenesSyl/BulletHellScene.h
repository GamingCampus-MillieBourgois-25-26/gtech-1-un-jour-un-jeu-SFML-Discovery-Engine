#pragma once

#include "BulletHellSyl/Player.h"
#include "BulletHellSyl/Enemy.h"
#include "BulletHellSyl/BulletComponent.h"
#include "BulletHellSyl/Star.h"
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
		Texture* starTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/star.png");

		// GameObjects
		GameObject* player = CreateGameObject("Player");
		player->CreateComponent<SpriteRenderer>(playerTex);
		player->CreateComponent<Player>();
		SquareCollider* collider = player->CreateComponent<SquareCollider>();
		collider->SetWidth({90.f});
		collider->SetHeight({60.f});
		collider->SetPivot({ 45.f, 30.f });
		player->SetPosition({ (float)window_size.x / 2, 500.f });
		player->SetScale({ 0.3f, 0.3f });

		GameObject* star1 = CreateGameObject("star1");
		SpriteRenderer* s1Renderer = star1->CreateComponent<SpriteRenderer>(starTex);
		SquareCollider* s1coll = star1->CreateComponent<SquareCollider>();
		s1coll->CopyFromSpriteRenderer(s1Renderer);
		Star* S1 = star1->CreateComponent<Star>(player);
		star1->SetPosition({ 300.f, 200.f });

		GameObject* star2 = CreateGameObject("star2");
		star2->CreateComponent<SpriteRenderer>(starTex);
		SquareCollider* s2coll = star2->CreateComponent<SquareCollider>();
		s2coll->CopyFromSpriteRenderer(s1Renderer);
		Star* S2 = star2->CreateComponent<Star>(player, S1);
		star2->SetPosition({ 50.f, (float)window_size.y - 50.f });
		star2->Disable();

		GameObject* star3 = CreateGameObject("star3");
		star3->CreateComponent<SpriteRenderer>(starTex);
		SquareCollider* s3coll = star3->CreateComponent<SquareCollider>();
		s3coll->CopyFromSpriteRenderer(s1Renderer);
		Star* S3 = star3->CreateComponent<Star>(player, S2);
		star3->SetPosition({ (float)window_size.x - 50.f, 50.f });
		star3->Disable();

		GameObject* star4 = CreateGameObject("star4");
		star4->CreateComponent<SpriteRenderer>(starTex);
		SquareCollider* s4coll = star4->CreateComponent<SquareCollider>();
		s4coll->CopyFromSpriteRenderer(s1Renderer);
		Star* S4 = star4->CreateComponent<Star>(player, S3);
		star4->SetPosition({ 300.f, 370.f });
		star4->Disable();

		GameObject* enemy = CreateGameObject("Enemy");
		enemy->CreateComponent<SpriteRenderer>(ennemyTex);
		enemy->CreateComponent<Enemy>();
		enemy->SetScale({ 0.5f, 0.5f });
		enemy->SetPosition({ (float)window_size.x / 2.f, (float)window_size.y / 2.f });
	}
};