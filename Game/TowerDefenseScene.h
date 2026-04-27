#pragma once
#include "Core/Scene.h"
#include "CellType.h"
#include "GridRenderer.h"
#include "WaveManager.h"
#include "TowerPlacementSystem.h"
#include "BaseTowerComponent.h"
#include "HUDComponent.h"
#include "TurretT.h"

namespace TowerDefence {
class TowerDefenseScene : public Scene
{
public:
    // Constructeur
    TowerDefenseScene();

    virtual ~TowerDefenseScene() = default;

    // Cycle de vie
    void Update(const float _delta_time) override;
        TowerDefenseScene();

        static constexpr int   GRID_WIDTH = 20;
        static constexpr int   GRID_HEIGHT = 13;
        static constexpr float CELL_SIZE = 50.f;
    void InitScene();

    private:

        void InitGrid();
    void HandlePlacement();

    bool m_isInitialized = false;
    bool m_isHoldingTurret = false;

        std::vector<std::vector<CellType>> grid;
        std::vector<Maths::Vector2i>       enemyPath;
    TurretType m_selectedType = TurretType::BASIC;
    };

}
#endif