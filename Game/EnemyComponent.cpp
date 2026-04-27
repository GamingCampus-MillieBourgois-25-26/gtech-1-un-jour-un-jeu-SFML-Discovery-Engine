#include "EnemyComponent.h"
#include "GameState.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>

namespace TowerDefence {

    Maths::Vector2f EnemyComponent::GridToWorld(const Maths::Vector2i& cell) const
    {
        return Maths::Vector2f(
            cell.x * cellSize + cellSize * 0.5f,
            cell.y * cellSize + cellSize * 0.5f
        );
    }

    void EnemyComponent::SetPath(const std::vector<Maths::Vector2i>& p, float cs)
    {
        path = p;
        cellSize = cs;
        currentWaypoint = 0;
        finished = false;
        dead = false;
        hp = maxHP;

        if (!path.empty())
        {
            worldTarget = GridToWorld(path[0]);
            GetOwner()->SetPosition(worldTarget);
        }
    }

    void EnemyComponent::TakeDamage(float amount)
    {
        if (dead) return;
        hp -= amount;
        if (hp <= 0.f)
        {
            dead = true;
            GameState::Get().money += reward; // récompense
        }
    }

    void EnemyComponent::Update(float dt)
    {
        if (finished || dead || path.empty()) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        float dx = worldTarget.x - pos.x;
        float dy = worldTarget.y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= speed * dt)
        {
            GetOwner()->SetPosition(worldTarget);
            currentWaypoint++;

            // Remplace ce bloc dans EnemyComponent::Update :
            if (currentWaypoint >= static_cast<int>(path.size()))
            {
                finished = true;
                // Cherche la BaseTower dans la scène pour lui infliger des dégâts
                Scene* scene = GetOwner()->GetScene();
                if (scene)
                {
                    GameObject* baseObj = scene->FindGameObject("BaseTower");
                    if (baseObj)
                    {
                        auto* base = baseObj->GetComponent<BaseTowerComponent>();
                        if (base) base->TakeDamage(damage);
                    }
                    else
                    {
                        // Fallback si pas de BaseTower : dégâts directs
                        GameState::Get().playerHP -= damage;
                        if (GameState::Get().playerHP <= 0)
                            GameState::Get().gameOver = true;
                    }
                }
                return;
            }

            worldTarget = GridToWorld(path[currentWaypoint]);
        }
        else
        {
            float nx = dx / dist;
            float ny = dy / dist;
            GetOwner()->SetPosition(Maths::Vector2f(
                pos.x + nx * speed * dt,
                pos.y + ny * speed * dt
            ));
        }
    }

    void EnemyComponent::Render(sf::RenderWindow* window)
    {
        if (finished || dead) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        float           radius = cellSize * 0.35f;

        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Red);
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setPosition(sf::Vector2f(pos.x, pos.y));
        window->draw(circle);

        // Barre de vie
        float barW = cellSize * 0.8f;
        float barH = 5.f;
        float barX = pos.x - barW * 0.5f;
        float barY = pos.y - radius - 8.f;

        sf::RectangleShape bgBar(sf::Vector2f(barW, barH));
        bgBar.setFillColor(sf::Color(80, 80, 80));
        bgBar.setPosition(sf::Vector2f(barX, barY));
        window->draw(bgBar);

        float ratio = std::max(0.f, hp / maxHP);
        sf::RectangleShape hpBar(sf::Vector2f(barW * ratio, barH));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(sf::Vector2f(barX, barY));
        window->draw(hpBar);
    }

    void EnemyComponent::Present()
    {
        if (dead || finished)
            GetOwner()->MarkForDeletion();
    }

    bool EnemyComponent::IsFinished() const { return finished; }
    bool EnemyComponent::IsDead()     const { return dead; }

}