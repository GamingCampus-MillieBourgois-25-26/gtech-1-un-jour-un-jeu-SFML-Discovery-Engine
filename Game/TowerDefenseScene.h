#pragma once
#include "CellType.h"
#include "Core/Scene.h"
#include "SFML/Graphics.hpp"
#include "GridRenderer.h"

class TowerDefenseScene final : public Scene {

public:

    TowerDefenseScene();

    static constexpr int GRID_WIDTH = 20;
    static constexpr int GRID_HEIGHT = 12;
    static constexpr float CELL_SIZE = 50.f;

    std::vector<std::vector<CellType>> grid;

private:

    void InitGrid();

    Maths::Vector2f GridToWorld(int x, int y) const;
};