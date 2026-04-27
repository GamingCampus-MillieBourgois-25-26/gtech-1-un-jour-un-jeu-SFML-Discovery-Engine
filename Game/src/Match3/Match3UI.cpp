#include "Match3/Match3UI.h"

#include "Core/GameObject.h"
#include "Components/TextRenderer.h"
#include "Maths/Vector2.h"
#include <SFML/Graphics/Color.hpp>


#include <string>

void Match3UI::Init(Scene* scene)
{
    m_scoreObject = scene->CreateGameObject("ScoreText");
    m_scoreObject->SetPosition(Maths::Vector2f(20.f, 20.f));

    m_scoreText = m_scoreObject->CreateComponent<TextRenderer>("Score: 0");
    m_scoreText->SetCharacterSize(24);
    m_scoreText->SetColor(sf::Color::Black);

    m_timerObject = scene->CreateGameObject("TimerText");
    m_timerObject->SetPosition(Maths::Vector2f(20.f, 60.f));

    m_timerText = m_timerObject->CreateComponent<TextRenderer>("Time: 60");
    m_timerText->SetCharacterSize(24);
    m_timerText->SetColor(sf::Color::Black);

    m_endObject = scene->CreateGameObject("EndText");
    m_endObject->SetPosition(Maths::Vector2f(180.f, 20.f));

    m_endText = m_endObject->CreateComponent<TextRenderer>("Game Over");
    m_endText->SetCharacterSize(48);
    m_endText->SetColor(sf::Color::Red);

    m_endObject->Disable();
}

void Match3UI::Update(int score, float timer, bool finished)
{
    if (m_scoreText)
    {
        m_scoreText->SetText("Score: " + std::to_string(score));
    }

    if (m_timerText)
    {
        m_timerText->SetText("Time: " + std::to_string(static_cast<int>(timer)));
    }

    if (m_endObject)
    {
        if (finished)
            m_endObject->Enable();
        else
            m_endObject->Disable();
    }
}