#include "TowerPlacementSystem.h"
#include "TowerComponent.h"
#include "SpawnQueue.h"
#include "GameState.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "InputModule.h"

namespace TowerDefence {

    void TowerPlacementSystem::SetConfig(
        std::vector<std::vector<CellType>>* g,
        const std::vector<Maths::Vector2i>& path,
        int w, int h, float cs)
    {
        grid = g;
        enemyPath = path;
        gridWidth = w;
        gridHeight = h;
        cellSize = cs;
    }

    void TowerPlacementSystem::Update(float dt)
    {
        if (GameState::Get().gameOver || GameState::Get().victory) return;

        bool clicking = InputModule::GetMouseButtonDown(sf::Mouse::Button::Left);

        if (clicking && !wasClickedLastFrame)
        {
            Maths::Vector2i mouse = InputModule::GetMousePosition();
            int gx = static_cast<int>(mouse.x / cellSize);
            int gy = static_cast<int>(mouse.y / cellSize);

            if (CanPlace(gx, gy) && GameState::Get().money >= towerCost)
            {
                GameState::Get().money -= towerCost;
                (*grid)[gy][gx] = CellType::Tower;
                pendingPlacement = true;
                pendingGx = gx;
                pendingGy = gy;
            }
        }

        wasClickedLastFrame = clicking;
    }

    void TowerPlacementSystem::Present()
    {
        if (!pendingPlacement) return;
        pendingPlacement = false;

        Scene* scene = GetOwner()->GetScene();
        float  cs = cellSize;
        int    gx = pendingGx;
        int    gy = pendingGy;

        SpawnQueue::Get().Push([scene, cs, gx, gy]()
            {
                GameObject* obj = scene->CreateGameObject("Tower");
                auto* tower = obj->CreateComponent<TowerComponent>();
                tower->cellSize = cs;
                obj->SetPosition(Maths::Vector2f(gx * cs, gy * cs));
            });
    }

    bool TowerPlacementSystem::CanPlace(int gx, int gy) const
    {
        if (gx < 0 || gx >= gridWidth || gy < 0 || gy >= gridHeight)
            return false;
        if ((*grid)[gy][gx] != CellType::Empty)
            return false;
        for (const auto& cell : enemyPath)
            if (cell.x == gx && cell.y == gy)
                return false;
        return true;
    }

    Maths::Vector2f TowerPlacementSystem::GridToWorld(int gx, int gy) const
    {
        return Maths::Vector2f(gx * cellSize, gy * cellSize);
    }

}