#pragma once
#include "Core/Component.h"
#include <string>

namespace TowerDefence {

    class ProjectileComponent : public Component
    {
    public:
        void Init(const std::string& targetName, float damage, float speed);
        void Update(float dt)              override;
        void Render(sf::RenderWindow* w)   override;
        void Present()                     override; //  destruction ici

    private:
        std::string targetName;
        float damage = 50.f;
        float speed = 300.f;
        bool  done = false;
    };

}