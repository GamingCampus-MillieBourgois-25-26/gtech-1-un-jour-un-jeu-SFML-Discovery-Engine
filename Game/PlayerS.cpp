#include "PlayerS.h"
#include "BulletS.h"

#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/InputModule.h"

#include <cmath>
#include <SFML/Graphics.hpp>

namespace BulletHell {

    void PlayerS::TakeHit()
    {
        if (hitCooldown > 0.f) return;
        lives--;
        hitCooldown = 2.f;
        BHGameState::Get().lives = lives;
        if (lives <= 0)
            BHGameState::Get().gameOver = true;
    }

    void PlayerS::HandleMovement(float dt)
    {
        Maths::Vector2f move = { 0.f, 0.f };
        if (InputModule::GetKey(sf::Keyboard::Key::Z)) move.y -= 1.f;
        if (InputModule::GetKey(sf::Keyboard::Key::S)) move.y += 1.f;
        if (InputModule::GetKey(sf::Keyboard::Key::Q)) move.x -= 1.f;
        if (InputModule::GetKey(sf::Keyboard::Key::D)) move.x += 1.f;

        float len = std::sqrt(move.x * move.x + move.y * move.y);
        if (len > 0.f) { move.x /= len; move.y /= len; }

        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x = std::max(radius, std::min(1000.f - radius, pos.x + move.x * speed * dt));
        pos.y = std::max(radius, std::min(600.f - radius, pos.y + move.y * speed * dt));
        GetOwner()->SetPosition(pos);
    }

    void PlayerS::Shoot()
    {
        Scene* scene = GetOwner()->GetScene();
        if (!scene) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();

        // Deux balles légèrement décalées
        for (float offX : { -8.f, 8.f })
        {
            static int bid = 0;
            GameObject* obj = scene->CreateGameObject("PBullet_" + std::to_string(bid++));
            obj->SetPosition({ pos.x + offX, pos.y - 10.f });
            auto* b = obj->CreateComponent<BulletS>();
            obj->SetPosition(Maths::Vector2f(pos.x + offX, pos.y - 10.f));
            b->speed = 700.f;
            b->isEnemy = false;
            b->radius = 5.f;
        }
    }

    void PlayerS::HandleShooting(float dt)
    {
        fireTimer += dt;
        if (InputModule::GetKey(sf::Keyboard::Key::Space) && fireTimer >= fireRate)
        {
            Shoot();
            fireTimer = 0.f;
        }
    }

    void PlayerS::Update(float dt)
    {
        if (BHGameState::Get().gameOver) return;
        if (hitCooldown > 0.f) hitCooldown -= dt;
        HandleMovement(dt);
        HandleShooting(dt);
    }

    void PlayerS::Render(sf::RenderWindow* window)
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();

        // Clignotement si invincible
        if (hitCooldown > 0.f && static_cast<int>(hitCooldown * 10) % 2 == 0)
            return;

        // Corps
        sf::CircleShape body(radius);
        body.setOrigin({ radius, radius });
        body.setPosition({ pos.x, pos.y });
        body.setFillColor(sf::Color(100, 180, 255));
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(2.f);
        window->draw(body);

        // Hitbox visible (petit point central)
        sf::CircleShape dot(3.f);
        dot.setOrigin({ 3.f, 3.f });
        dot.setPosition({ pos.x, pos.y });
        dot.setFillColor(sf::Color::White);
        window->draw(dot);
    }

}