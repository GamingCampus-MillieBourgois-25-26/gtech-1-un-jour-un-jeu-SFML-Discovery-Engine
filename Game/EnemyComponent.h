#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "BaseTowerComponent.h"
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
        int   reward = 25;       // argent donné à la mort
        int   damage = 3;        // dégâts au joueur si arrivé au bout
        float speed = 120.f;

        void SetStats(float _maxHp, float _speed, int _reward) {

            maxHP = _maxHp;
            hp = _maxHp;
            speed = _speed;
            reward = _reward;
        }

    private:
        std::vector<Maths::Vector2i> path;
        float cellSize = 50.f;
        int   currentWaypoint = 0;
        
        Maths::Vector2f worldTarget;
        bool  finished = false;
        bool  dead = false;

        Maths::Vector2f GridToWorld(const Maths::Vector2i& cell) const;
    };

}