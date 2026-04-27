#include "Match3/Match3Controller.h"

#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/AssetsModule.h"
#include "Modules/InputModule.h"

#include "Core/GameObject.h"
#include "Assets/Texture.h"

#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Color.hpp>

namespace Match3
{
    void Match3Controller::Start()
    {
        LoadAssets();

        CreateBackground();

        board.Init(8, 8);

        ui.Init(GetOwner()->GetScene());

        CreateTiles();
        UpdateTiles();
    }

    void Match3Controller::Update(float deltaTime)
    {
        if (!gameFinished)
        {
            timer -= deltaTime;

            if (timer <= 0.f)
            {
                timer = 0.f;
                gameFinished = true;
            }

            if (waitingResolve)
            {
                resolveTimer -= deltaTime;

                if (resolveTimer <= 0.f)
                {
                    waitingResolve = false;

                    waitingDestroy = true;
                    destroyTimer = 0.25f;
                }
            }
            else if (waitingDestroy)
            {
                destroyTimer -= deltaTime;

                if (destroyTimer <= 0.f)
                {
                    waitingDestroy = false;
                    ResolveBoard();
                }
            }
            else
            {
                HandleInput();
            }
        }

        UpdateTiles();
        ui.Update(board.GetScore(), timer, gameFinished);
    }

    void Match3Controller::LoadAssets()
    {
        AssetsModule* assets = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<AssetsModule>();

        redTexture = assets->LoadAsset<Texture>("Match3/candy_red.png");
        blueTexture = assets->LoadAsset<Texture>("Match3/candy_blue.png");
        greenTexture = assets->LoadAsset<Texture>("Match3/candy_green.png");
        yellowTexture = assets->LoadAsset<Texture>("Match3/candy_yellow.png");
        purpleTexture = assets->LoadAsset<Texture>("Match3/candy_purple.png");
        bgTexture = assets->LoadAsset<Texture>("Match3/bg_new.jpg");
    }

    void Match3Controller::CreateBackground()
    {
        Scene* scene = GetOwner()->GetScene();

        GameObject* bg = scene->CreateGameObject("Match3Background");

        bg->SetPosition(Maths::Vector2f(0.f, 0.f));
        bg->SetScale(Maths::Vector2f(0.5f, 0.5f));

        bg->CreateComponent<SpriteRenderer>(bgTexture);
    }

    void Match3Controller::CreateTiles()
    {
        Scene* scene = GetOwner()->GetScene();

        candyObjects.clear();
        selectionObjects.clear();

        for (int y = 0; y < board.GetHeight(); ++y)
        {
            for (int x = 0; x < board.GetWidth(); ++x)
            {
                float px = offsetX + x * tileSize;
                float py = offsetY + y * tileSize;

                GameObject* selection = scene->CreateGameObject("Match3Selection");
                selection->SetPosition(Maths::Vector2f(px, py));
                selection->SetScale(Maths::Vector2f(tileSize, tileSize));

                RectangleShapeRenderer* selectionRenderer =
                    selection->CreateComponent<RectangleShapeRenderer>();

                selectionRenderer->SetColor(sf::Color::White);
                selection->Disable();

                selectionObjects.push_back(selection);

                std::array<GameObject*, 5> candies;

                candies[0] = CreateCandyObject(scene, redTexture, px, py);
                candies[1] = CreateCandyObject(scene, blueTexture, px, py);
                candies[2] = CreateCandyObject(scene, greenTexture, px, py);
                candies[3] = CreateCandyObject(scene, yellowTexture, px, py);
                candies[4] = CreateCandyObject(scene, purpleTexture, px, py);

                candyObjects.push_back(candies);
            }
        }
    }

    GameObject* Match3Controller::CreateCandyObject(Scene* scene, Texture* texture, float px, float py)
    {
        GameObject* obj = scene->CreateGameObject("Match3Candy");

        obj->SetPosition(Maths::Vector2f(
            px + tileSize * 0.5f,
            py + tileSize * 0.5f
        ));

        obj->SetScale(candyScale);
        obj->CreateComponent<SpriteRenderer>(texture);
        obj->Disable();

        return obj;
    }

    void Match3Controller::HandleInput()
    {
        if (!InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
        {
            return;
        }

        Maths::Vector2i mousePos = InputModule::GetMousePosition();

        int x = static_cast<int>((mousePos.x - offsetX) / tileSize);
        int y = static_cast<int>((mousePos.y - offsetY) / tileSize);

        if (x < 0 || x >= board.GetWidth() || y < 0 || y >= board.GetHeight())
        {
            selectedX = -1;
            selectedY = -1;
            return;
        }

        if (selectedX == -1 || selectedY == -1)
        {
            selectedX = x;
            selectedY = y;
            return;
        }

        if (board.Swap(selectedX, selectedY, x, y))
        {
            waitingResolve = true;
            resolveTimer = 0.15f;
        }

        selectedX = -1;
        selectedY = -1;
    }

    void Match3Controller::ResolveBoard()
    {
        board.ResolveMatches();

        while (board.FindMatches())
        {
            board.ResolveMatches();
        }
    }

    void Match3Controller::UpdateTiles()
    {
        for (int y = 0; y < board.GetHeight(); ++y)
        {
            for (int x = 0; x < board.GetWidth(); ++x)
            {
                int index = y * board.GetWidth() + x;

                for (GameObject* obj : candyObjects[index])
                {
                    obj->Disable();
                }

                int candyIndex = GetCandyIndex(board.GetCandy(x, y));

                if (candyIndex >= 0)
                {
                    GameObject* candy = candyObjects[index][candyIndex];

                    candy->Enable();

                    if (waitingDestroy && board.IsMarked(x, y))
                    {
                        candy->SetScale(Maths::Vector2f(
                            candyScale.x * 1.35f,
                            candyScale.y * 1.35f
                        ));
                    }
                    else if (x == selectedX && y == selectedY)
                    {
                        candy->SetScale(Maths::Vector2f(
                            candyScale.x * 1.15f,
                            candyScale.y * 1.15f
                        ));
                    }
                    else
                    {
                        candy->SetScale(candyScale);
                    }
                }

                if (x == selectedX && y == selectedY)
                {
                    selectionObjects[index]->Enable();
                }
                else
                {
                    selectionObjects[index]->Disable();
                }
            }
        }
    }

    int Match3Controller::GetCandyIndex(CandyType type) const
    {
        switch (type)
        {
        case CandyType::Red:
            return 0;
        case CandyType::Blue:
            return 1;
        case CandyType::Green:
            return 2;
        case CandyType::Yellow:
            return 3;
        case CandyType::Purple:
            return 4;
        case CandyType::Empty:
        default:
            return -1;
        }
    }
}