#pragma once
#include "Core/Component.h"
#include <SFML/Graphics.hpp>

namespace TowerDefence {

    class BaseTowerComponent : public Component
    {
    public:
        void Render(sf::RenderWindow* window) override;

        // Les ennemis appelleront cette méthode en fin de chemin
        // (tu remplaces le dégât direct au playerHP dans EnemyComponent)
        void TakeDamage(int amount);

        int hp = 30;
        int maxHp = 30;

        float cellSize = 50.f;

        sf::Color color = sf::Color(255, 140, 0);  // orange vif
    };

}