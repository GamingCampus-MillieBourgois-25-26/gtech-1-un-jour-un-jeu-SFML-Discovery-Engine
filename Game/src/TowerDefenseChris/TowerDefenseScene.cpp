#include "TowerDefenseChris/TowerDefenseScene.h"
#include "TowerDefenseChris/InputTowerComponent.h"
#include "TowerDefenseChris/EnemyComponent.h"
#include "TowerDefenseChris/SpawnerComponent.h"
#include "TowerDefenseChris/GameManagerComponent.h"
#include "TowerDefenseChris/TowerComponent.h"
#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/AssetsModule.h"

#include "Core/GameObject.h"
#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include "Maths/Vector2.h"

TowerDefense::TowerDefenseScene::TowerDefenseScene()
    : Scene("TowerDefenseScene")
{
    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    Texture* mapTexture = assets->LoadAsset<Texture>("TowerDefenseChris/set/map.png");
    Texture* enemyTex = assets->LoadAsset<Texture>("TowerDefenseChris/set/enemy.png");
    Texture* towerTex = assets->LoadAsset<Texture>("TowerDefenseChris/set/tower.png");

    GameObject* map = CreateGameObject("Map");
    map->SetPosition(Maths::Vector2f(320.f, 320.f));
    map->SetScale(Maths::Vector2f(4.f, 4.f));
    map->CreateComponent<SpriteRenderer>(mapTexture);

    for (int i = 0; i < 20; ++i)
    {
        GameObject* enemy = CreateGameObject("Enemy_" + std::to_string(i));
        enemy->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
        enemy->SetScale(Maths::Vector2f(2.f, 2.f));
        enemy->CreateComponent<SpriteRenderer>(enemyTex);
        enemy->CreateComponent<EnemyComponent>();
    }

    for (int i = 0; i < 30; ++i)
    {
        GameObject* tower = CreateGameObject("TowerPool_" + std::to_string(i));
        tower->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
        tower->SetScale(Maths::Vector2f(1.f, 1.f));
        tower->CreateComponent<SpriteRenderer>(towerTex);
        tower->CreateComponent<TowerComponent>();
    }

    InputTowerComponent::scene = this;

    GameObject* spawner = CreateGameObject("Spawner");
    spawner->CreateComponent<SpawnerComponent>();

    GameObject* gameManager = CreateGameObject("GameManager");
    gameManager->CreateComponent<GameManagerComponent>();

    GameObject* inputObj = CreateGameObject("Input");
    inputObj->CreateComponent<InputTowerComponent>();
}