#include "GridRenderer.h"

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
}