#pragma once
#include "CellType.h"
#include "Core/Scene.h"

class TowerDefenseScene final : public Scene {

  public:

    TowerDefenseScene();

  private:

     void InitGrid();

     static constexpr int GRID_WIDTH = 20;
     static constexpr int GRID_HEIGHT = 12;
     static constexpr float CELL_SIZE = 50.f;

     std::vector<std::vector<CellType>> grid;

     Maths::Vector2f GridToWorld(int x, int y) const {

         return Maths::Vector2f(
             x * CELL_SIZE + CELL_SIZE * 0.5f,
             y * CELL_SIZE + CELL_SIZE * 0.5f
         );
     }
};