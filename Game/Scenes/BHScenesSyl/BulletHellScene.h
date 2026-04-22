#pragma once

#include "BulletHellSyl/Player.h"
#include "BulletHellSyl/Enemy.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include <vector>

class BulletHellScene final : public Scene
{
public:
	BulletHellScene() : Scene("BulletHellScene")
	{
		GameObject* player = CreateDummyGameObject("Player", { 250.f, 400.f });
		player->CreateComponent<Player>();

		GameObject* enemy = CreateDummyGameObject("Enemy", { 100.f, 250.f });
		enemy->CreateComponent<Enemy>();

		//GameObject* enemy2 = CreateDummyGameObject("Enemy2", { 0.f, 50.f }, sf::Color::Yellow);

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* playerTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/playerShip.png");
		Texture* ennemyTex = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/ufoRed.png");
		Texture* laserBlue = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/laserBlue.png");

		player->CreateComponent<SpriteRenderer>(playerTex);
		enemy->CreateComponent<SpriteRenderer>(ennemyTex);
	}

	GameObject* CreateDummyGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(20.f);
		square_collider->SetHeight(20.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		//shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(20.f, 20.f));

		return game_object;
	}

	std::vector<GameObject*> bullets;
};