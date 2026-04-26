#include "BHHUD.h"
#include "BHGameState.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    void BHHUD::Start()
    {
        fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");
        if (!fontLoaded)
            fontLoaded = font.openFromFile("arial.ttf");
    }

    void BHHUD::DrawText(sf::RenderWindow* w, const std::string& txt,
        float x, float y, unsigned sz, sf::Color col)
    {
        if (!fontLoaded) return;
        sf::Text shadow(font, txt, sz);
        shadow.setFillColor(sf::Color(0, 0, 0, 160));
        shadow.setPosition({ x + 2.f, y + 2.f });
        w->draw(shadow);
        sf::Text t(font, txt, sz);
        t.setFillColor(col);
        t.setPosition({ x, y });
        w->draw(t);
    }

    void BHHUD::Render(sf::RenderWindow* window)
    {
        if (!fontLoaded) return;
        auto& gs = BHGameState::Get();

        // Bandeau haut
        sf::RectangleShape bar({ 1000.f, 38.f });
        bar.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(bar);

        DrawText(window, "Score: " + std::to_string(gs.score),
            10.f, 6.f, 22, sf::Color::White);
        DrawText(window, "Vague: " + std::to_string(gs.wave) + "/3",
            400.f, 6.f, 22, sf::Color(255, 215, 0));

        // Vies (cercles)
        for (int i = 0; i < gs.lives; i++)
        {
            sf::CircleShape heart(10.f);
            heart.setFillColor(sf::Color(220, 50, 50));
            heart.setPosition({ 850.f + i * 30.f, 8.f });
            window->draw(heart);
        }

        // Game Over
        if (gs.gameOver)
        {
            sf::RectangleShape overlay({ 1000.f, 600.f });
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            window->draw(overlay);
            DrawText(window, "GAME OVER", 330.f, 230.f, 64, sf::Color::Red);
            DrawText(window, "Score final: " + std::to_string(gs.score),
                360.f, 320.f, 28, sf::Color::White);
            DrawText(window, "Relancez pour rejouer",
                310.f, 370.f, 22, sf::Color(200, 200, 200));
        }

        // Victoire
        if (gs.victory)
        {
            sf::RectangleShape overlay({ 1000.f, 600.f });
            overlay.setFillColor(sf::Color(0, 0, 0, 140));
            window->draw(overlay);
            DrawText(window, "VICTOIRE !", 320.f, 230.f, 64, sf::Color::Yellow);
            DrawText(window, "Score final: " + std::to_string(gs.score),
                360.f, 320.f, 28, sf::Color::White);
        }
    }

}