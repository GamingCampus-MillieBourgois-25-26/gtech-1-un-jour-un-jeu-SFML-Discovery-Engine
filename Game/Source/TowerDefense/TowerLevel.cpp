#include "TowerDefense/TowerLevel.h"

TowerDefense::TowerLevel::TowerLevel() : Scene("TowerLevel")
{
	float caseWidth = 100.f;
	float caseHeight = 100.f;

	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	// Texture* textureBackground = assets_module->LoadAsset<Texture>("wallpaperVoxel.jpg");
	Texture* caseShop = assets_module->LoadAsset<Texture>("TowerDefense/caseShop.png");
	Texture* TextureSoldierGreen = assets_module->LoadAsset<Texture>("TowerDefense/Soldier_Green.png");

	// GameObject* background = CreateGameObject("Background");
	// background->CreateComponent<SpriteRenderer>(textureBackground);

	GameObject* shopCase1 = CreateGameObject("Tour_Simple");
	shopCase1->CreateComponent<SpriteRenderer>(caseShop);
	shopCase1->CreateComponent<Shop>(sf::Vector2f{ 0.f, 550.f });

	GameObject* shopCase2 = CreateGameObject("Tour_Double");
	shopCase2->CreateComponent<SpriteRenderer>(caseShop);
	shopCase2->CreateComponent<Shop>(sf::Vector2f{ 50.f, 550.f });

	GameObject* shopCase3 = CreateGameObject("Mur");
	shopCase3->CreateComponent<SpriteRenderer>(caseShop);
	shopCase3->CreateComponent<Shop>(sf::Vector2f{ 100.f, 550.f });

	GameObject* player = CreateGameObject("Player");
	player->CreateComponent<Player>(100);

	// ENEMY

	for (int i = 0; i < 3; i++)
	{
		GameObject* soldierGreen = CreateGameObject("soldierGreen" + std::to_string(i));
		soldierGreen->CreateComponent<Enemy>(100, 100, 100, 0);
		soldierGreen->CreateComponent<SpriteRenderer>(TextureSoldierGreen);
		soldierGreen->SetPosition({ 0.f + -i * 50, 0.f });
		soldierGreen->SetScale({ 0.5f, 0.5f });
	}
}

//void TowerDefense::TowerLevel::SpawnDefense()
//{
//	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
//	// ...
//}

//void TowerDefense::TowerLevel::SpawnEnemy(int typeEnemy)
//{
//	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
//	Texture* textureSoldierGreen = assets_module->LoadAsset<Texture>("TowerDefense/Soldier_Green.png");
//	Texture* textureSoldierYellow = assets_module->LoadAsset<Texture>("TowerDefense/Soldier_Yellow.png");
//	Texture* textureSoldierRed = assets_module->LoadAsset<Texture>("TowerDefense/Soldier_Red.png");
//
//	GameObject* soldier = nullptr;
//
//	switch (typeEnemy)
//	{
//	case 0:
//		soldier = CreateGameObject("Soldier_Green");
//		soldier->CreateComponent<SpriteRenderer>(textureSoldierGreen);
//		break;
//
//	case 1:
//		soldier = CreateGameObject("Soldier_Yellow");
//		soldier->CreateComponent<SpriteRenderer>(textureSoldierYellow);
//		break;
//
//	case 2:
//		soldier = CreateGameObject("Soldier_Red");
//		soldier->CreateComponent<SpriteRenderer>(textureSoldierRed);
//		break;
//
//	default:
//		Logger::Log(ELogLevel::Error, "Ennemi introuvable.");
//		break;
//	}
//}
