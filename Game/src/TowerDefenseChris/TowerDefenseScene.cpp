#include "TowerDefenseChris/TowerDefenseScene.h"
#include "TowerDefenseChris/InputTowerComponent.h"
#include "TowerDefenseChris/EnemyComponent.h"
#include "TowerDefenseChris/SpawnerComponent.h"
#include "TowerDefenseChris/GameManagerComponent.h"

#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "Maths/Vector2.h"

TowerDefense::TowerDefenseScene::TowerDefenseScene()
    : Scene("TowerDefenseScene")
{
    const int rows = 5;
    const int cols = 8;
    const float cellSize = 80.f;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            GameObject* cell = CreateGameObject("Cell_" + std::to_string(x) + "_" + std::to_string(y));
            cell->SetPosition(Maths::Vector2f(x * cellSize, y * cellSize));
            cell->SetScale(Maths::Vector2f(1.f, 1.f));

            RectangleShapeRenderer* renderer = cell->CreateComponent<RectangleShapeRenderer>();
            renderer->SetSize(Maths::Vector2f(cellSize - 2.f, cellSize - 2.f));

            if (y == 2)
                renderer->SetColor(sf::Color(180, 120, 60));
            else
                renderer->SetColor(sf::Color(60, 160, 60));
        }
    }

    GameObject* enemy = CreateGameObject("Enemy_Start");
    enemy->SetPosition(Maths::Vector2f(20.f, 2.f * cellSize + 20.f));
    enemy->SetScale(Maths::Vector2f(1.f, 1.f));

    RectangleShapeRenderer* enemyRenderer = enemy->CreateComponent<RectangleShapeRenderer>();
    enemyRenderer->SetSize(Maths::Vector2f(40.f, 40.f));
    enemyRenderer->SetColor(sf::Color::Red);

    enemy->CreateComponent<EnemyComponent>();

    InputTowerComponent::scene = this;
    SpawnerComponent::scene = this;

    GameObject* spawner = CreateGameObject("Spawner");
    spawner->CreateComponent<SpawnerComponent>();

    GameObject* gameManager = CreateGameObject("GameManager");
    gameManager->CreateComponent<GameManagerComponent>();

    GameObject* inputObj = CreateGameObject("Input");
    inputObj->CreateComponent<InputTowerComponent>();
}