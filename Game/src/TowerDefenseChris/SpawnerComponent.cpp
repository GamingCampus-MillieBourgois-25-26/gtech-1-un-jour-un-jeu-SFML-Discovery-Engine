#include "TowerDefenseChris/SpawnerComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "TowerDefenseChris/EnemyComponent.h"
#include "Maths/Vector2.h"

Scene* SpawnerComponent::scene = nullptr;

void SpawnerComponent::Update(float _delta_time)
{
    timer += _delta_time;

    if (timer < 2.0f)
        return;

    timer = 0.f;

    GameObject* enemy = scene->CreateGameObject("Enemy");

    enemy->SetPosition(Maths::Vector2f(20.f, 2.f * 80.f + 20.f));
    enemy->SetScale(Maths::Vector2f(1.f, 1.f));

    auto r = enemy->CreateComponent<RectangleShapeRenderer>();
    r->SetSize(Maths::Vector2f(40.f, 40.f));
    r->SetColor(sf::Color::Red);

    enemy->CreateComponent<EnemyComponent>();
}