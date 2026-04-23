#include "TowerDefenseScene.h"


TowerDefenseScene::TowerDefenseScene()
    : Scene("TowerDefenseScene")
{
    GameObject* gridObj = CreateGameObject("Grid");

    auto* gridRenderer = gridObj->CreateComponent<GridRenderer>();
    gridRenderer->width = GRID_WIDTH;
    gridRenderer->height = GRID_HEIGHT;
    gridRenderer->cellSize = CELL_SIZE;
}

void TowerDefenseScene::InitGrid()
{
}

