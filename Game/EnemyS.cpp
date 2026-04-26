#include "EnemyS.h"
#include "BulletS.h"
#include "BHGameState.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>
#include <SFML/Graphics.hpp>

static constexpr float PI = 3.14159265f;

namespace BulletHell {

    void EnemyS::TakeDamage(float dmg)
    {
        if (dead) return;
        hp -= dmg;
        if (hp <= 0.f)
        {
            dead = true;
            BHGameState::Get().score += scoreValue;
        }
    }

    void EnemyS::ShootLine()
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();

        // 3 balles vers le bas
        for (int i = -1; i <= 1; i++)
        {
            static int eid = 0;
            GameObject* obj = scene->CreateGameObject("EBullet_" + std::to_string(eid++));
            obj->SetPosition(pos);
            auto* b = obj->CreateComponent<BulletS>();
            b->direction = Maths::Vector2f(i * 0.3f, 1.f);
            float len = std::sqrt(b->direction.x * b->direction.x + b->direction.y * b->direction.y);
            b->direction.x /= len;
            b->direction.y /= len;
            b->speed   = 220.f;
            b->isEnemy = true;
            b->radius  = 6.f;
        }
    }

    void EnemyS::ShootSpiral(float dt)
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();

        angle += 180.f * dt;  // rotation de la spirale
        float rad = angle * PI / 180.f;

        for (int i = 0; i < 4; i++)
        {
            float a = rad + i * (PI / 2.f);
            static int sid = 0;
            GameObject* obj = scene->CreateGameObject("EBullet_" + std::to_string(sid++));
            obj->SetPosition(pos);
            auto* b = obj->CreateComponent<BulletS>();
            b->direction = Maths::Vector2f(std::cos(a), std::sin(a));
            b->speed   = 180.f;
            b->isEnemy = true;
            b->radius  = 5.f;
        }
    }

    void EnemyS::ShootBurst()
    {
        Scene* scene = GetOwner()->GetScene();
        Maths::Vector2f pos = GetOwner()->GetPosition();

        // 8 balles dans toutes les directions
        for (int i = 0; i < 8; i++)
        {
            float a = i * (2.f * PI / 8.f);
            static int bid = 0;
            GameObject* obj = scene->CreateGameObject("EBullet_" + std::to_string(bid++));
            obj->SetPosition(pos);
            auto* b = obj->CreateComponent<BulletS>();
            b->direction = Maths::Vector2f(std::cos(a), std::sin(a));
            b->speed   = 160.f;
            b->isEnemy = true;
            b->radius  = 6.f;
        }
    }

    void EnemyS::Update(float dt)
    {
        if (dead || done || BHGameState::Get().gameOver) return;

        // Mouvement
        Maths::Vector2f pos = GetOwner()->GetPosition();
        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
        GetOwner()->SetPosition(pos);

        // Hors écran par le bas
        if (pos.y > 660.f) { done = true; return; }

        // Tir
        shootTimer += dt;

        if (pattern == EnemyPattern::Spiral)
        {
            ShootSpiral(dt);  // continu
        }
        else if (shootTimer >= shootRate)
        {
            shootTimer = 0.f;
            if (pattern == EnemyPattern::Line)  ShootLine();
            if (pattern == EnemyPattern::Burst) ShootBurst();
        }
    }

    void EnemyS::Render(sf::RenderWindow* window)
    {
        if (dead || done) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();

        sf::CircleShape body(radius);
        body.setOrigin({ radius, radius });
        body.setPosition({ pos.x, pos.y });

        sf::Color col = sf::Color(80, 200, 80);
        if (pattern == EnemyPattern::Spiral) col = sf::Color(200, 80, 200);
        if (pattern == EnemyPattern::Burst)  col = sf::Color(200, 140, 30);
        body.setFillColor(col);
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(2.f);
        window->draw(body);
    }

    void EnemyS::Present()
    {
        if (dead || done)
            GetOwner()->MarkForDeletion();
    }

}