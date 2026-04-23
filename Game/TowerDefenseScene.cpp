#include "TowerDefenseScene.h"


TowerDefenseScene::TowerDefenseScene() : Scene("TowerDefenseScene") {
    InitGrid();
}

void TowerDefenseScene::InitGrid() { 

    grid.resize(GRID_HEIGHT);

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        grid[y].resize(GRID_WIDTH, CellType::Empty);
    }
}