#include "TowerDefenseScene.h"
#include "BaseTowerComponent.h"
#include "SpawnQueue.h"
#include "GameState.h"
#include "HUDComponent.h"

namespace TowerDefence {

    TowerDefenseScene::TowerDefenseScene()
        : Scene("TowerDefenseScene")
    {
        GameState::Get().Reset();

        // Grille visuelle
        GameObject* gridObj = CreateGameObject("Grid");
        auto* gridRenderer = gridObj->CreateComponent<GridRenderer>();
        gridRenderer->width = GRID_WIDTH;
        gridRenderer->height = GRID_HEIGHT;
        gridRenderer->cellSize = CELL_SIZE;

        InitGrid();

        // Chemin complexe en zigzag — reste dans 20x13, arrive en {10,6} (centre)
        enemyPath = {
            // Entrée par le bord gauche, ligne 1
            {0,1},{1,1},{2,1},{3,1},{4,1},{5,1},
            // Descend
            {5,2},{5,3},{5,4},
            // Repart à gauche puis descend encore
            {4,4},{3,4},{2,4},{1,4},
            {1,5},{1,6},{1,7},{1,8},
            // Traverse vers la droite
            {2,8},{3,8},{4,8},{5,8},{6,8},{7,8},
            // Remonte
            {7,7},{7,6},{7,5},{7,4},
            // Continue à droite
            {8,4},{9,4},{10,4},{11,4},{12,4},
            // Descend vers le centre
            {12,5},{12,6},
            // Arrive sur la base
            {11,6},{10,6}
        };

        gridRenderer->path = enemyPath;

        // Marque les cellules du chemin comme non-placables
        for (const auto& cell : enemyPath)
            (*&grid)[cell.y][cell.x] = CellType::Path;

        // WaveManager
        GameObject* waveObj = CreateGameObject("WaveManager");
        auto* waveManager = waveObj->CreateComponent<WaveManager>();
        waveManager->SetConfig(enemyPath, CELL_SIZE);

        // TowerPlacementSystem
        GameObject* placementObj = CreateGameObject("PlacementSystem");
        auto* placement = placementObj->CreateComponent<TowerPlacementSystem>();
        placement->SetConfig(&grid, enemyPath, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);
        placement->towerCost = 50;

        // HUD
        GameObject* hudObj = CreateGameObject("HUD");
        auto* hud = hudObj->CreateComponent<HUDComponent>();
        hud->towerCost = placement->towerCost;

        // BaseTower — case centrale {10,6}, carrée VERTE
        GameObject* baseObj = CreateGameObject("BaseTower");
        auto* base = baseObj->CreateComponent<BaseTowerComponent>();
        base->cellSize = CELL_SIZE;
        base->hp = 30;
        base->maxHp = 30;
        base->color = sf::Color(50, 200, 50);  // vert vif
        GameState::Get().playerHP = base->hp;
        // Centre de la cellule {10,6}
        baseObj->SetPosition(Maths::Vector2f(
            10 * CELL_SIZE + CELL_SIZE * 0.5f,
            6 * CELL_SIZE + CELL_SIZE * 0.5f
        ));
        // Marque la cellule comme non-placable
        grid[6][10] = CellType::Tower;
    }

    void TowerDefenseScene::InitGrid()
    {
        grid.assign(GRID_HEIGHT, std::vector<CellType>(GRID_WIDTH, CellType::Empty));
    }
}