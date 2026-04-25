#include "BaseTowerComponent.h"
#include "GameState.h"
#include "Core/GameObject.h"
#include <algorithm>

namespace TowerDefence {

    void BaseTowerComponent::TakeDamage(int amount)
    {
        hp -= amount;
        // Synchronise avec le GameState pour que le HUD l'affiche
        GameState::Get().playerHP = hp;
        if (hp <= 0)
        {
            hp = 0;
            GameState::Get().gameOver = true;
        }
    }

    void BaseTowerComponent::Render(sf::RenderWindow* window)
    {
        Maths::Vector2f pos = GetOwner()->GetPosition();
        float           size = cellSize * 0.9f;

        // Carré principal (orange)
        sf::RectangleShape body(sf::Vector2f(size, size));
        body.setFillColor(color);
        body.setOutlineColor(sf::Color::White);
        body.setOutlineThickness(2.f);
        body.setPosition({ pos.x - size * 0.5f, pos.y - size * 0.5f });
        window->draw(body);

        // Barre de vie de la base
        float barW = cellSize * 1.2f;
        float barH = 6.f;
        float barX = pos.x - barW * 0.5f;
        float barY = pos.y - size * 0.5f - 12.f;

        sf::RectangleShape bgBar(sf::Vector2f(barW, barH));
        bgBar.setFillColor(sf::Color(80, 80, 80));
        bgBar.setPosition({ barX, barY });
        window->draw(bgBar);

        float ratio = static_cast<float>(std::max(0, hp)) / static_cast<float>(maxHp);
        sf::RectangleShape hpBar(sf::Vector2f(barW * ratio, barH));
        hpBar.setFillColor(sf::Color(255, 80, 80));
        hpBar.setPosition({ barX, barY });
        window->draw(hpBar);
    }

} 