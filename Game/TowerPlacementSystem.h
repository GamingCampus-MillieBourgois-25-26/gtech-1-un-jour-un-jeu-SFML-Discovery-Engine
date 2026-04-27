#pragma once
#include "Core/Component.h"
#include "CellType.h"
#include "Maths/Vector2.h"
#include <vector>

namespace TowerDefence {

    class TowerPlacementSystem : public Component {
    public:
        void SetConfig(
            std::vector<std::vector<CellType>>* grid,
            const std::vector<Maths::Vector2i>& enemyPath,
            int gridWidth, int gridHeight, float cellSize
        );

        void Update(float dt) override;
        void Present()        override;

        int towerCost = 50;   // ← coût d'une tour

    private:
        bool CanPlace(int gx, int gy) const;

        Maths::Vector2f GridToWorld(int gx, int gy) const;

        std::vector<std::vector<CellType>>* grid = nullptr;
        std::vector<Maths::Vector2i> enemyPath;

        int   gridWidth = 20;
        int   gridHeight = 12;
        float cellSize = 50.f;

        bool wasClickedLastFrame = false;
        bool pendingPlacement = false;
        int  pendingGx = 0;
        int  pendingGy = 0;
    };

}