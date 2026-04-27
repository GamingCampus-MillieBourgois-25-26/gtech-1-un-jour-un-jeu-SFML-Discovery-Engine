#include "HUDComponent.h"
#include <string>

namespace TowerDefence {

    void HUDComponent::Start()
    {
        // Font statique : chargée une seule fois, jamais détruite/réinitialisée
        static sf::Font sharedFont;
        static bool     sharedFontLoaded = false;

        if (!sharedFontLoaded)
        {
            const char* paths[] = {
                "C:/Windows/Fonts/arial.ttf",
                "C:/Windows/Fonts/segoeui.ttf",
                "C:/Windows/Fonts/tahoma.ttf",
                nullptr
            };
            for (int i = 0; paths[i] != nullptr; ++i)
            {
                if (sharedFont.openFromFile(paths[i]))
                {
                    sharedFontLoaded = true;
                    break;
                }
            }
        }

        if (sharedFontLoaded)
        {
            fontPtr = &sharedFont;
            fontLoaded = true;
        }
    }

    void HUDComponent::DrawText(sf::RenderWindow* window,
        const std::string& text,
        float x, float y,
        unsigned int size,
        sf::Color color)
    {
        if (!fontLoaded) return;
        sf::Text shadow(*fontPtr, sf::String(text), size);
        shadow.setFillColor(sf::Color(0, 0, 0, 180));
        shadow.setPosition(sf::Vector2f(x + 2.f, y + 2.f));
        window->draw(shadow);

        sf::Text t(*fontPtr, sf::String(text), size);
        t.setFillColor(color);
        t.setPosition(sf::Vector2f(x, y));
        window->draw(t);
    }

    void HUDComponent::Render(sf::RenderWindow* window)
    {
        if (!fontLoaded) return;
        GameState& gs = GameState::Get();

        sf::RectangleShape banner(sf::Vector2f(1000.f, 40.f));
        banner.setFillColor(sf::Color(0, 0, 0, 160));
        banner.setPosition(sf::Vector2f(0.f, 0.f));
        window->draw(banner);

        DrawText(window, "HP: " + std::to_string(gs.playerHP), 10.f, 8.f, 22,
            gs.playerHP > 5 ? sf::Color(220, 50, 50) : sf::Color::Red);
        DrawText(window, "$ " + std::to_string(gs.money), 160.f, 8.f, 22,
            sf::Color(255, 215, 0));
        DrawText(window, "Vague " + std::to_string(gs.currentWave)
            + " / " + std::to_string(gs.maxWaves), 360.f, 8.f, 22,
            sf::Color::White);

        std::string costStr = "Tour: " + std::to_string(towerCost) + "$";
        DrawText(window, costStr, 600.f, 8.f, 22,
            gs.money >= towerCost ? sf::Color(100, 255, 100) : sf::Color(200, 80, 80));

        // Game Over — affiché seulement si gameOver est true
        if (gs.gameOver)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            window->draw(overlay);
            DrawText(window, "GAME OVER", 330.f, 250.f, 60, sf::Color::Red);
            DrawText(window, "Relancez le programme pour rejouer",
                220.f, 330.f, 22, sf::Color::White);
        }

        // Victoire — affiché seulement si victory est true
        if (gs.victory)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 140));
            window->draw(overlay);
            DrawText(window, "VICTOIRE !", 320.f, 250.f, 60, sf::Color::Yellow);
            DrawText(window, "Toutes les vagues repoussees !",
                250.f, 330.f, 22, sf::Color::White);
        }
    }
}