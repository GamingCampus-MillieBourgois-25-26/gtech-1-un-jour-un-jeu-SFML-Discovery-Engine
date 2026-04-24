#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace TowerDefence {

    class EnemyComponent : public Component
    {
    public:
        void SetPath(const std::vector<Maths::Vector2i>& path, float cellSize);
        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;
        void Present() override;
        void  TakeDamage(float amount);
        bool  IsFinished() const;
        bool  IsDead()     const;

        float maxHP = 100.f;
        float hp = 100.f;

    private:
        std::vector<Maths::Vector2i> path;
        float cellSize = 50.f;

        int   currentWaypoint = 0;
        float speed = 120.f;

        Maths::Vector2f worldTarget;
        bool  finished = false;
        bool  dead = false;

        Maths::Vector2f GridToWorld(const Maths::Vector2i& cell) const;
    };

}