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

Maths::Vector2f TowerDefenseScene::GridToWorld(int x, int y) const
{
    return Maths::Vector2f();
}

