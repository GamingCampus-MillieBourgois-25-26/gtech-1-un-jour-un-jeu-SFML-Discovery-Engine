#include "TowerDefenseScene.h"
#include "SpawnFlusher.h"

namespace TowerDefence {

    TowerDefenseScene::TowerDefenseScene()
        : Scene("TowerDefenseScene")
    {
        // Grille visuelle
        GameObject* gridObj = CreateGameObject("Grid");
        auto* gridRenderer = gridObj->CreateComponent<GridRenderer>();
        gridRenderer->width = GRID_WIDTH;
        gridRenderer->height = GRID_HEIGHT;
        gridRenderer->cellSize = CELL_SIZE;

        InitGrid();

        enemyPath = {
            {0,2},{1,2},{2,2},{3,2},{4,2},
            {5,2},{6,2},{7,2},{8,2},{9,2},
            {9,3},{9,4},{9,5},{9,6},{9,7},
            {10,7},{11,7},{12,7},{13,7},{14,7},
            {15,7},{16,7},{17,7},{18,7},{19,7}
        };

        // WaveManager
        GameObject* waveObj = CreateGameObject("WaveManager");
        auto* waveManager = waveObj->CreateComponent<WaveManager>();
        waveManager->SetConfig(enemyPath, CELL_SIZE);

        // TowerPlacementSystem
        GameObject* placementObj = CreateGameObject("PlacementSystem");
        auto* placement = placementObj->CreateComponent<TowerPlacementSystem>();
        placement->SetConfig(&grid, enemyPath, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);

        // SpawnFlusher — doit être le DERNIER GameObject créé
        // pour que son Present() s'exécute après tous les autres
        GameObject* flusherObj = CreateGameObject("SpawnFlusher");
        flusherObj->CreateComponent<SpawnFlusher>();
    }

    void TowerDefenseScene::InitGrid()
    {
        grid.assign(GRID_HEIGHT, std::vector<CellType>(GRID_WIDTH, CellType::Empty));
    }

}