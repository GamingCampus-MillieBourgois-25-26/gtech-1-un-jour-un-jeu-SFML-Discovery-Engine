#pragma once
#include "Core/Component.h"

#include "SFML/Graphics.hpp"

namespace TowerDefence {

    class EnemyComponent;

    class TowerComponent : public Component {

    public:

        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;
        void Present() override;

        float cellSize = 50.f;
        float range = 100.f;
        float fireRate = 1.f;
        float damage = 20.f;

        sf::Color color = sf::Color(30, 144, 255);

    private:
        float fireTimer = 0.f;

        bool  hasPendingShot = false;

        std::string pendingTarget;

        EnemyComponent* FindClosestEnemy();
    };

}