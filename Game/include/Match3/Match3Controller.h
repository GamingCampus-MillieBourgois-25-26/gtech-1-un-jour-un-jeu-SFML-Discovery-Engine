#pragma once

#include "Core/Component.h"
#include "Match3/Match3Board.h"
#include "Match3/Match3UI.h"

#include <vector>
#include <array>

class Texture;
class GameObject;

namespace Match3
{
    class Match3Controller : public Component
    {
    public:
        void Start() override;
        void Update(float deltaTime) override;

    private:
        Match3Board board;
        Match3UI ui;

        Texture* redTexture = nullptr;
        Texture* blueTexture = nullptr;
        Texture* greenTexture = nullptr;
        Texture* yellowTexture = nullptr;
        Texture* purpleTexture = nullptr;
        Texture* bgTexture = nullptr;

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
        void LoadAssets();
        void CreateBackground();
        void CreateTiles();
        GameObject* CreateCandyObject(Scene* scene, Texture* texture, float px, float py);
        void HandleInput();
        void UpdateTiles();
        int GetCandyIndex(CandyType type) const;
    };
}