#pragma once

#include <vector>

#include "Core/GameObject.h"

namespace bulletHell
{
    class PlayerController;

    class PlayerHUDComponent final : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;

        void SetPlayer(PlayerController* _player);
        void AddLifePip(GameObject* _lifePip);

    private:
        void RefreshLives();

    private:
        PlayerController* player = nullptr;
        std::vector<GameObject*> lifePips;
        int maxLives = 0;
    };
}