#include "MenuScene.h"
#include "ButtonComponent.h"
#include "RectangleShapeRenderer.h"

MenuScene::MenuScene() : Scene("MenuScene")
{
    CreateButton("Play TD", Maths::Vector2f(200, 200), ButtonTarget::TowerDefense);
    CreateButton("Play Bullet Hell", Maths::Vector2f(200, 320), ButtonTarget::BulletHell);
}

void MenuScene::CreateButton(const std::string& name,
    const Maths::Vector2f& pos,
    ButtonTarget target)
{
    GameObject* button = CreateGameObject(name);
    button->SetPosition(pos);
    button->SetScale(Maths::Vector2f(220, 70));

    auto* rect = button->CreateComponent<RectangleShapeRenderer>();
    rect->SetColor(target == ButtonTarget::TowerDefense
        ? sf::Color::Blue
        : sf::Color(140, 0, 180));

    auto* btn = button->CreateComponent<ButtonComponent>();
    btn->target = target;
}