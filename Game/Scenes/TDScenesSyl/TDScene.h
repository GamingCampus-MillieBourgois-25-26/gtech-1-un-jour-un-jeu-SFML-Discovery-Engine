#pragma once
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "TowerDefenseSyl/EnemyAComponent.h"
#include "TowerDefenseSyl/TowerAComponent.h"
#include "TowerDefenseSyl/tileComponent.h"
#include "TowerDefenseSyl/Spawner.h"
#include "TowerDefenseSyl/ProjectileComponent.h"
#include "Modules/WindowModule.h"
#include "Modules/AssetsModule.h"

class TDScene final : public Scene
{
public:
	TDScene() : Scene("Tower Defense")
	{
		// load textures
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* tileTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/tile.png");
		Texture* roadTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/road.png");
		Texture* towerATex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/towerA.png");
		Texture* bulletTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/bullet.png");

		CreateMap();
		GameObject* tower = CreateGameObject("tower");
		GameObject* spawner = CreateGameObject("spawner");
		GameObject* enemy = CreateGameObject("enemy");
		GameObject* player = CreateGameObject("player");

		spawner->CreateComponent<Spawner>(path);

		tower->SetPosition({tileSize * 2, tileSize * 2 });
		enemy->CreateComponent<EnemyAComponent>(path);
		tower->CreateComponent<TowerAComponent>();
		tower->CreateComponent<SpriteRenderer>(towerATex);
		tower->SetScale({ 0.25f,0.25f });

		enemy->SetPosition(spawnPoint);
		RectangleShapeRenderer* shape_renderer = enemy->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(sf::Color::Yellow);
		shape_renderer->SetSize(Maths::Vector2f(20.f, 20.f));

		/*Maths::Vector2f a = { 200.f, 200.f };
		Maths::Vector2f b = { 100.f, 100.f };
		GameObject* projectile = CreateGameObject("projectile");
		projectile->CreateComponent<ProjectileComponent>(a);
		projectile->SetPosition(b);
		projectile->CreateComponent<SpriteRenderer>(bulletTex);*/
	}

	void CreateMap()
	{
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				GameObject* tile = CreateGameObject("tile");
				tile->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/tile.png"));
				tile->SetPosition({ x * tileSize, y * tileSize });
				tile->SetScale({ 0.25f,0.25f });
			}
		}
		for (int i = 0; i < roads.size(); ++i)
		{
			GameObject* road = CreateGameObject("road");
			road->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/road.png"));
			road->SetPosition(roads[i]);
			road->SetScale({ 0.25f,0.25f });
		}
	};

	Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();
	int height = 20;
	int width = 20;
	float tileSize = 32.f;
	Maths::Vector2f spawnPoint = { -16.f, 32.f };
	std::vector<Maths::Vector2f> path = {
		{tileSize * 1.f,tileSize * 1.f},
		{tileSize * 1.f,tileSize * 9.f},
		{tileSize * 7.f,tileSize * 9.f},
		{tileSize * 7.f,tileSize * 2.f},
		{tileSize * 11.f,tileSize * 2.f},
		{tileSize * 11.f,tileSize * 15.f},
		{tileSize * 2.f,tileSize * 15.f},
	};
	std::vector<Maths::Vector2f> roads = {
		{ 0 * tileSize, 1 * tileSize },
		{ 1 * tileSize, 1 * tileSize },
		{ 1 * tileSize, 2 * tileSize },
		{ 1 * tileSize, 3 * tileSize },
		{ 1 * tileSize, 4 * tileSize },
		{ 1 * tileSize, 5 * tileSize },
		{ 1 * tileSize, 6 * tileSize },
		{ 1 * tileSize, 7 * tileSize },
		{ 1 * tileSize, 8 * tileSize },
		{ 1 * tileSize, 9 * tileSize },
		{ 2 * tileSize, 9 * tileSize },
		{ 3 * tileSize, 9 * tileSize },
		{ 4 * tileSize, 9 * tileSize },
		{ 5 * tileSize, 9 * tileSize },
		{ 6 * tileSize, 9 * tileSize },
		{ 7 * tileSize, 9 * tileSize },
		{ 7 * tileSize, 8 * tileSize },
		{ 7 * tileSize, 7 * tileSize },
		{ 7 * tileSize, 6 * tileSize },
		{ 7 * tileSize, 5 * tileSize },
		{ 7 * tileSize, 4 * tileSize },
		{ 7 * tileSize, 3 * tileSize },
		{ 7 * tileSize, 2 * tileSize },
		{ 8 * tileSize, 2 * tileSize },
		{ 9 * tileSize, 2 * tileSize },
		{ 10 * tileSize, 2 * tileSize },
		{ 11 * tileSize, 2 * tileSize },
		{ 11 * tileSize, 3 * tileSize },
		{ 11 * tileSize, 4 * tileSize },
		{ 11 * tileSize, 5 * tileSize },
		{ 11 * tileSize, 6 * tileSize },
		{ 11 * tileSize, 7 * tileSize },
		{ 11 * tileSize, 8 * tileSize },
		{ 11 * tileSize, 9 * tileSize },
		{ 11 * tileSize, 10 * tileSize },
		{ 11 * tileSize, 11 * tileSize },
		{ 11 * tileSize, 12 * tileSize },
		{ 11 * tileSize, 13 * tileSize },
		{ 11 * tileSize, 14 * tileSize },
		{ 11 * tileSize, 15 * tileSize },
		{ 10 * tileSize, 15 * tileSize },
		{ 9 * tileSize, 15 * tileSize },
		{ 8 * tileSize, 15 * tileSize },
		{ 7 * tileSize, 15 * tileSize },
		{ 6 * tileSize, 15 * tileSize },
		{ 5 * tileSize, 15 * tileSize },
		{ 4 * tileSize, 15 * tileSize },
		{ 3 * tileSize, 15 * tileSize },
		{ 2 * tileSize, 15 * tileSize },
	};
};
