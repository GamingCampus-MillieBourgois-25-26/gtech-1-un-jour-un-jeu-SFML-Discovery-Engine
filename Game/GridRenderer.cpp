#include "GridRenderer.h"

namespace TowerDefence {

    void GridRenderer::Render(sf::RenderWindow* window)
    {
        sf::RectangleShape cellShape;
        cellShape.setSize(sf::Vector2f(cellSize - 1.f, cellSize - 1.f));

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                sf::Vector2f pos(
                    x * cellSize,
                    y * cellSize
                );

                cellShape.setPosition(pos);
                cellShape.setFillColor(sf::Color(50, 50, 50));

                window->draw(cellShape);
            }
        }

        for (const auto& cell : path) {

            sf::RectangleShape pathCell(sf::Vector2f(cellSize - 2.f, cellSize - 2.f));
            pathCell.setFillColor(sf::Color(180, 140, 80, 120));
            pathCell.setPosition(sf::Vector2f(cell.x * cellSize + 1.f, cell.y * cellSize + 1.f));
            window->draw(pathCell);
        }
    }
}