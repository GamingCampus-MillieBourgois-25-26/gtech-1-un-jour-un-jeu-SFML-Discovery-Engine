#pragma once
#include "Core/Scene.h"
#include "CellType.h"
#include "GridRenderer.h"
#include "WaveManager.h"
#include "TowerPlacementSystem.h"
#include "BaseTowerComponent.h"
#include "HUDComponent.h"

namespace TowerDefence {

    class TowerDefenseScene final : public Scene {
    public:

        TowerDefenseScene();

        static constexpr int   GRID_WIDTH = 20;
        static constexpr int   GRID_HEIGHT = 13;
        static constexpr float CELL_SIZE = 50.f;

    private:

        void InitGrid();

        std::vector<std::vector<CellType>> grid;
        std::vector<Maths::Vector2i>       enemyPath;
    };

}