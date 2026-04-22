#pragma once

#include "Core/Component.h"

namespace bulletHell
{
    class PlayerController;

    class PlayerHUDComponent final : public Component
    {
    public:
        void OnGUI() override;

        void SetPlayer(PlayerController* _player);

    private:
        PlayerController* player = nullptr;
    };
}