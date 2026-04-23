#pragma once
#include "SFML/Graphics.hpp"
#include "Core/Component.h"

class GridRenderer : public Component {

public:

    void Render(sf::RenderWindow* window) override;

    int width;
    int height;
    float cellSize;
};
