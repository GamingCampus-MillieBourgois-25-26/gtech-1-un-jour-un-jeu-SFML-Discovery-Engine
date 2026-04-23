#include "TDScene.h"

#include "Engine.h"
#include "GameObject.h"
#include "RectangleShapeRenderer.h"
#include "WindowModule.h"

using namespace TD;

TDScene::TDScene() : Scene("TDScene")
{
    CreateMap();
    CreatePath();
}


void TDScene::CreateMap()
{
    const int tileSize = 64;

    const Maths::Vector2u window_size =
        Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

    int width = window_size.x / tileSize;
    int height = window_size.y / tileSize;

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            GameObject* tile = CreateGameObject("Tile");

            tile->SetPosition(Maths::Vector2f(
                static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize)
            ));

            auto* renderer = tile->CreateComponent<RectangleShapeRenderer>();

            renderer->SetSize(Maths::Vector2f(
                static_cast<float>(tileSize - 1),
                static_cast<float>(tileSize - 1)
            ));

            renderer->SetColor(sf::Color(50, 50, 50));
        }
    }
}

void TDScene::CreatePath()
{
    pathPoints = {
        {0.f, 200.f},
        {300.f, 200.f},
        {300.f, 400.f},
        {600.f, 400.f},
        {600.f, 100.f},
        {900.f, 100.f}
    };

    for (const auto& point : pathPoints)
    {
        GameObject* node = CreateGameObject("PathNode");

        node->SetPosition(point);

        auto* renderer = node->CreateComponent<RectangleShapeRenderer>();

        renderer->SetSize(Maths::Vector2f(10.f, 10.f));
        renderer->SetColor(sf::Color::Red);
    }
}