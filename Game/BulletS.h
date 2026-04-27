#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

namespace BulletHell {

    class BulletS : public Component
    {
    public:
        Maths::Vector2f direction = { 0.f, -1.f };
        float           speed = 600.f;
        bool            isEnemy = false;   // true = balle ennemie
        float           radius = 5.f;

        void Update(float dt) override;
        void Render(sf::RenderWindow* window) override;
        void Present() override;

    private:
        bool done = false;
    };

}