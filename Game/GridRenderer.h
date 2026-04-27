#pragma once
#include "SFML/Graphics.hpp"
#include "Core/Component.h"

namespace TowerDefence {

    class GridRenderer : public Component {

    public:

        void Render(sf::RenderWindow* window) override;

        int width = 20;
        int height = 12;
        float cellSize = 50.f;

        std::vector<Maths::Vector2i> path;
    };

}