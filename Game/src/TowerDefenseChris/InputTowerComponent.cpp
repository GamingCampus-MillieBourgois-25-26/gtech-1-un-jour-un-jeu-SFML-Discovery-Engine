#include "TowerDefenseChris/InputTowerComponent.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Modules/InputModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "TowerDefenseChris/TowerComponent.h"
#include "Maths/Vector2.h"
#include <SFML/Window/Mouse.hpp>
#include <string>


Scene* InputTowerComponent::scene = nullptr;

#include <iostream>

void InputTowerComponent::Update(float _delta_time)
{
    if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
        return;

    std::cout << "clic detecte\n";

    if (scene == nullptr)
    {
        std::cout << "scene nullptr\n";
        return;
    }

    Maths::Vector2i mouse = InputModule::GetMousePosition();
    std::cout << "mouse: " << mouse.x << ", " << mouse.y << "\n";

    const float cellSize = 80.f;

    int x = mouse.x / cellSize;
    int y = mouse.y / cellSize;

    std::cout << "cell: " << x << ", " << y << "\n";

    if (y == 2)
    {
        std::cout << "clic sur le chemin\n";
        return;
    }

    std::string towerName = "Tower_" + std::to_string(x) + "_" + std::to_string(y);
    GameObject* tower = scene->CreateGameObject(towerName);

    if (tower == nullptr)
    {
        std::cout << "tower nullptr\n";
        return;
    }

    std::cout << "tour creee\n";

    tower->SetPosition(Maths::Vector2f(x * cellSize + 20.f, y * cellSize + 20.f));
    tower->SetScale(Maths::Vector2f(1.f, 1.f));

    RectangleShapeRenderer* r = tower->CreateComponent<RectangleShapeRenderer>();

    if (r == nullptr)
    {
        std::cout << "renderer nullptr\n";
        return;
    }

    r->SetSize(Maths::Vector2f(40.f, 40.f));
    r->SetColor(sf::Color::Yellow);

    tower->CreateComponent<TowerComponent>();

    std::cout << "tour finalisee\n";
}