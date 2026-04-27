#pragma once
#include "Core/Component.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>

namespace TowerDefence {
    class HUDComponent : public Component
    {
    public:
        HUDComponent() = default;
        HUDComponent(const HUDComponent&) = delete;
        HUDComponent& operator=(const HUDComponent&) = delete;

        void Start()  override;
        void Render(sf::RenderWindow* window) override;

        int towerCost = 50;

    private:
        sf::Font* fontPtr = nullptr;   // ← pointeur vers la font statique
        bool      fontLoaded = false;

        void DrawText(sf::RenderWindow* window,
            const std::string& text,
            float x, float y,
            unsigned int size,
            sf::Color color);
    };
}