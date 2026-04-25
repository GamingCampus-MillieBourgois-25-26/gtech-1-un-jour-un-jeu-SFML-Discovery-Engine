#include "BulletS.h"
#include "Core/GameObject.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    void BulletS::Update(float dt)
    {
        if (done) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += direction.x * speed * dt;
        pos.y += direction.y * speed * dt;
        GetOwner()->SetPosition(pos);

        // Hors écran
        if (pos.x < -60.f || pos.x > 1060.f || pos.y < -60.f || pos.y > 660.f)
        {
            done = true;
        }
    }

    void BulletS::Render(sf::RenderWindow* window)
    {
        if (done) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        sf::CircleShape c(radius);
        c.setOrigin({ radius, radius });
        c.setPosition({ pos.x, pos.y });
        c.setFillColor(isEnemy ? sf::Color(255, 80, 80) : sf::Color(80, 200, 255));
        window->draw(c);
    }

    void BulletS::Present()
    {
        if (done)
            GetOwner()->MarkForDeletion();
    }

}