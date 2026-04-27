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
#include "TowerDefenseSyl/Container.h"
#include "TowerDefenseSyl/SelectedTower.h"
#include "TowerDefenseSyl/TowerASelection.h"
#include "Modules/WindowModule.h"
#include "TowerDefenseSyl/HQComponent.h"
#include "Modules/AssetsModule.h"
#include "Components/TextRenderer.h"
#include <vector>

class TDScene final : public Scene
{
public:
	TDScene() : Scene("Tower Defense")
	{
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		// load textures
		Texture* tileTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/tile.png");
		Texture* roadTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/road.png");
		Texture* towerATex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/towerA.png");
		Texture* bulletTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/bullet.png");
		Texture* QGTex = assets_module->LoadAsset<Texture>("Sylvain/TowerDefense/QG.png");

		map.resize(20);
		for (int i = 0; i < 20; ++i) {
			map[i].resize(15);
		}

		//_______________GameObjects________________
		GameObject* selector = CreateGameObject("selection");
		SelectedTower* selectComp = selector->CreateComponent<SelectedTower>();
		
		//Create Map
		HQComponent* QGComp;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width - 5; ++x)
			{
				if (mapSheet[y][x] == 1)
				{
					GameObject* road = CreateGameObject("road");
					road->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/road.png"));
					road->SetPosition({ x * tileSize + offset, y * tileSize + offset });
					road->SetScale({ 0.22f,0.22f });
					map[y][x] = road;
				}
				else if (mapSheet[y][x] == 0)
				{
					GameObject* tile = CreateGameObject("tile");
					tile->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/tile.png"));
					RectangleShapeRenderer* shape = tile->CreateComponent<RectangleShapeRenderer>();
					shape->SetColor(sf::Color::Transparent);
					shape->SetSize(Maths::Vector2f(125.f, 125.f));
					shape->SetPivot({ 13.5f, 13.8f });
					tile->CreateComponent<Container>(shape, selectComp);
					tile->SetPosition({ x * tileSize + offset, y * tileSize + offset });
					tile->SetScale({ 0.22f,0.22f });
					map[y][x] = tile;
				}
				else
				{
					GameObject* QG = CreateGameObject("QG");
					QG->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/QG.png"));
					QGComp = QG->CreateComponent<HQComponent>();
					QG->SetPosition({ x * tileSize + offset, y * tileSize + offset - 3.f });
					QG->SetScale({ 2.f,2.1f });

				}
			}
		}

		//

		GameObject* spawner = CreateGameObject("spawner");
		spawner->CreateComponent<Spawner>(path, QGComp);

		GameObject* selectTowerA = CreateGameObject("selection");
		RectangleShapeRenderer* shapeA = selectTowerA->CreateComponent<RectangleShapeRenderer>();
		shapeA->SetColor(sf::Color::Transparent);
		shapeA->SetSize(Maths::Vector2f(125.f, 125.f));
		shapeA->SetPivot({ 30.f, 30.f });
		selectTowerA->CreateComponent<SpriteRenderer>(towerATex);
		selectTowerA->CreateComponent<TowerASelection>(shapeA, selectComp);
		selectTowerA->SetPosition({ (float)window_size.x - 80.f , 120.f });
		selectTowerA->SetScale({ 0.5f, 0.5f });

		GameObject* tours = CreateGameObject("display");
		tours->SetPosition({ (float)window_size.x - 125.f , 10.f });
		TextRenderer* text = tours->CreateComponent<TextRenderer>("Tours");
		text->SetColor(sf::Color::Cyan);

		GameObject* player = CreateGameObject("player");
	}

	Maths::Vector2u window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();
	int height = 20;
	int width = 20;
	float offset = 15.f;
	float tileSize = window_size.x / 20.f;
	Maths::Vector2f spawnPoint = { -16.f, 32.f };
	std::vector<std::vector<GameObject*>> map;
	std::vector<std::vector<int>> mapSheet =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	std::vector<Maths::Vector2f> path = {
		{tileSize * 1.f,tileSize * 1.f},
		{tileSize * 1.f,tileSize * 9.f},
		{tileSize * 7.f,tileSize * 9.f},
		{tileSize * 7.f,tileSize * 2.f},
		{tileSize * 11.f,tileSize * 2.f},
		{tileSize * 11.f,tileSize * 15.f},
		{tileSize * 2.f,tileSize * 15.f},
	};
};
