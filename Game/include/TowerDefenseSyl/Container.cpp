#include "Container.h"
#include "TowerDefenseSyl/Tower.h"
#include "Components/SpriteRenderer.h"
#include "Modules/AssetsModule.h"
#include "Core/Scene.h"
#include "InputModule.h"
#include <iostream>

Container::Container(RectangleShapeRenderer* shap, SelectedTower* select, int* argent)
{
    shape = shap;
    selector = select;
    gold = argent;
}

void Container::Update(float _delta_time)
{
    if (IsUnderCursor())
    {
        shape->SetColor(sf::Color::Cyan);
        if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left) && empty == true)
        {
            AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            Type* tower = selector->GetSelectedTower();
            if (tower == nullptr)
                return;
            if (*tower == Type::A && *gold >= 5)
            {
                empty = false;
                *gold -= 5;
                GameObject* newTower = GetOwner()->GetScene()->CreateGameObject("tower");
                newTower->CreateComponent<Tower>(Type::A);
                newTower->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/towerA.png"));
                newTower->SetScale({ 0.25f,0.25f });
                newTower->SetPosition(GetOwner()->GetPosition());
            }
            if (*tower == Type::B && *gold >= 10)
            {
                empty = false;
                *gold -= 10;
                GameObject* newTower = GetOwner()->GetScene()->CreateGameObject("tower");
                newTower->CreateComponent<Tower>(Type::B);
                newTower->CreateComponent<SpriteRenderer>(assets_module->GetAsset<Texture>("Sylvain/TowerDefense/towerB.png"));
                newTower->SetScale({ 0.25f,0.25f });
                newTower->SetPosition(GetOwner()->GetPosition());
            }
        }
    }
    else
    {
        shape->SetColor(sf::Color::Transparent);
    }
}

bool Container::IsUnderCursor()
{
    const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

    Maths::Vector2f position = GetOwner()->GetPosition();
    position -= {15.f, 15.f};
    const Maths::Vector2f& size = {30.f, 30.f};

    const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size));

    return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}