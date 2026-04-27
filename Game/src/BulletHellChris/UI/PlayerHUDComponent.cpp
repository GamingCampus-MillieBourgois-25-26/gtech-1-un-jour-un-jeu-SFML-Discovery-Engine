#include "BulletHellChris/UI/PlayerHUDComponent.h"

#include "Components/RectangleShapeRenderer.h"
#include "BulletHellChris/Components/PlayerController.h"

namespace bulletHell
{
    void PlayerHUDComponent::Start()
    {
        if (player != nullptr)
        {
            maxLives = player->GetLives();
        }

        RefreshLives();
    }

    void PlayerHUDComponent::Update(float _delta_time)
    {
        (void)_delta_time;
        RefreshLives();
    }

    void PlayerHUDComponent::SetPlayer(PlayerController* _player)
    {
        player = _player;

        if (player != nullptr)
        {
            maxLives = player->GetLives();
        }
    }

    void PlayerHUDComponent::AddLifePip(GameObject* _lifePip)
    {
        if (_lifePip == nullptr)
        {
            return;
        }

        lifePips.push_back(_lifePip);
    }

    void PlayerHUDComponent::RefreshLives()
    {
        if (player == nullptr)
        {
            return;
        }

        const int currentLives = player->GetLives();

        for (int i = 0; i < static_cast<int>(lifePips.size()); ++i)
        {
            GameObject* pipObject = lifePips[i];
            if (pipObject == nullptr)
            {
                continue;
            }

            RectangleShapeRenderer* renderer = pipObject->GetComponent<RectangleShapeRenderer>();
            if (renderer == nullptr)
            {
                continue;
            }

            if (i < currentLives)
            {
                renderer->SetColor(sf::Color(80, 255, 120));
            }
            else
            {
                renderer->SetColor(sf::Color(70, 70, 70));
            }
        }
    }
}