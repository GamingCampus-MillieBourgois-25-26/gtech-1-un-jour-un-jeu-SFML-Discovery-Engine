#include "Match3/Match3Scene.h"
#include "Match3/Match3Board.h"
#include "Match3/Match3UI.h"

#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/AssetsModule.h"
#include "Modules/InputModule.h"

#include "Core/Component.h"
#include "Core/GameObject.h"

#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h"

#include "Maths/Vector2.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Color.hpp>

#include <array>
#include <vector>

namespace
{
    class Match3Controller : public Component
    {
    public:
        void Start() override
        {
            LoadAssets();

            board.Init(8, 8);

            ui.Init(GetOwner()->GetScene());

            CreateTiles();
            UpdateTiles();
        }

        void Update(float deltaTime) override
        {
            if (!gameFinished)
            {
                timer -= deltaTime;

                if (timer <= 0.f)
                {
                    timer = 0.f;
                    gameFinished = true;
                }

                HandleInput();
            }

            UpdateTiles();
            ui.Update(board.GetScore(), timer, gameFinished);
        }

    private:
        Match3Board board;
        Match3UI ui;

        Texture* redTexture = nullptr;
        Texture* blueTexture = nullptr;
        Texture* greenTexture = nullptr;
        Texture* yellowTexture = nullptr;
        Texture* purpleTexture = nullptr;

        std::vector<std::array<GameObject*, 5>> candyObjects;
        std::vector<GameObject*> selectionObjects;

        int selectedX = -1;
        int selectedY = -1;

        float timer = 60.f;
        bool gameFinished = false;

        float tileSize = 48.f;
        float offsetX = 100.f;
        float offsetY = 100.f;

        Maths::Vector2f candyScale = Maths::Vector2f(0.5f, 0.5f);

    private:
        void LoadAssets()
        {
            AssetsModule* assets = Engine::GetInstance()
                ->GetModuleManager()
                ->GetModule<AssetsModule>();

            redTexture = assets->LoadAsset<Texture>("Match3/candy_red.png");
            blueTexture = assets->LoadAsset<Texture>("Match3/candy_blue.png");
            greenTexture = assets->LoadAsset<Texture>("Match3/candy_green.png");
            yellowTexture = assets->LoadAsset<Texture>("Match3/candy_yellow.png");
            purpleTexture = assets->LoadAsset<Texture>("Match3/candy_purple.png");
        }

        void CreateTiles()
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

        GameObject* CreateCandyObject(Scene* scene, Texture* texture, float px, float py)
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

        void HandleInput()
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
                board.ResolveMatches();

                while (board.FindMatches())
                {
                    board.ResolveMatches();
                }
            }

            selectedX = -1;
            selectedY = -1;
        }

        void UpdateTiles()
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

                        if (x == selectedX && y == selectedY)
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

        int GetCandyIndex(CandyType type) const
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
    };
}

namespace Match3
{
    Match3Scene::Match3Scene()
        : Scene("Match3Scene")
    {
        GameObject* controller = CreateGameObject("Match3Controller");
        controller->CreateComponent<Match3Controller>();
    }
}