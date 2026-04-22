#include "BulletHell/UI/BossHUDComponent.h"

#include "Components/RectangleShapeRenderer.h"
#include "BulletHell/Components/BossComponent.h"
#include "Maths/Vector2.h"

namespace bulletHell
{
    void BossHUDComponent::Start()
    {
        RefreshBar();
    }

    void BossHUDComponent::Update(float _delta_time)
    {
        (void)_delta_time;
        RefreshBar();
    }

    void BossHUDComponent::SetBoss(BossComponent* _boss)
    {
        boss = _boss;
    }

    void BossHUDComponent::SetBarBackground(GameObject* _barBackground)
    {
        barBackground = _barBackground;
    }

    void BossHUDComponent::SetBarFill(GameObject* _barFill)
    {
        barFill = _barFill;
    }

    void BossHUDComponent::RefreshBar()
    {
        if (boss == nullptr)
        {
            return;
        }

        const float maxHealth = boss->GetMaxHealth();
        const float currentHealth = boss->GetCurrentHealth();

        float ratio = 0.0f;
        if (maxHealth > 0.0f)
        {
            ratio = currentHealth / maxHealth;
        }

        if (ratio < 0.0f)
        {
            ratio = 0.0f;
        }
        if (ratio > 1.0f)
        {
            ratio = 1.0f;
        }

        if (barBackground != nullptr)
        {
            RectangleShapeRenderer* backgroundRenderer = barBackground->GetComponent<RectangleShapeRenderer>();
            if (backgroundRenderer != nullptr)
            {
                backgroundRenderer->SetSize(Maths::Vector2f(maxBarWidth, barHeight));
                backgroundRenderer->SetColor(sf::Color(40, 40, 40));
            }
        }

        if (barFill != nullptr)
        {
            RectangleShapeRenderer* fillRenderer = barFill->GetComponent<RectangleShapeRenderer>();
            if (fillRenderer != nullptr)
            {
                fillRenderer->SetSize(Maths::Vector2f(maxBarWidth * ratio, barHeight));

                if (ratio > 0.66f)
                {
                    fillRenderer->SetColor(sf::Color(80, 255, 120));
                }
                else if (ratio > 0.33f)
                {
                    fillRenderer->SetColor(sf::Color(255, 210, 60));
                }
                else
                {
                    fillRenderer->SetColor(sf::Color(255, 80, 80));
                }
            }
        }
    }
}