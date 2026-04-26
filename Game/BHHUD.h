#pragma once
#include "Core/Component.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    class BHHUD : public Component
    {
    public:
        void Start()  override;
        void Render(sf::RenderWindow* window) override;

    private:
        sf::Font font;
        bool     fontLoaded = false;

        void DrawText(sf::RenderWindow* w, const std::string& txt,
            float x, float y, unsigned sz, sf::Color col);
    };

}