#include "TowerDefenseChris/InputTowerComponent.h"
#include "TowerDefenseChris/TowerComponent.h"
#include "TowerDefenseChris/GameManagerComponent.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Modules/InputModule.h"
#include "Maths/Vector2.h"

#include <SFML/Window/Mouse.hpp>

Scene* InputTowerComponent::scene = nullptr;

void InputTowerComponent::Update(float _delta_time)
{
    if (GameManagerComponent::gameOver || GameManagerComponent::victory)
        return;

    if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
        return;

    Maths::Vector2i mouse = InputModule::GetMousePosition();

    const int rows = 10;
    const int cols = 10;
    const float cellSize = 64.f;

    const int x = static_cast<int>(mouse.x / cellSize);
    const int y = static_cast<int>(mouse.y / cellSize);

    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return;

    bool isPathCell =
        (x == 0 && y == 2) ||
        (x == 1 && y == 2) ||
        (x == 2 && y >= 2 && y <= 7) ||
        (x == 3 && y == 7) ||
        (x == 4 && y >= 1 && y <= 7) ||
        (x == 5 && y == 1) ||
        (x == 6 && y >= 1 && y <= 5) ||
        (x == 7 && y == 5) ||
        (x == 8 && y == 5) ||
        (x == 9 && y == 5);

    if (isPathCell)
        return;

    float px = x * cellSize + 16.f;
    float py = y * cellSize + 16.f;

    for (TowerComponent* tower : TowerComponent::towers)
    {
        if (tower != nullptr && !tower->IsActive())
        {
            tower->ActivateAt(px, py);
            break;
        }
    }
}