#pragma once

#include "Core/GameObject.h"

namespace bulletHell
{
    class BossComponent;

    class BossHUDComponent final : public Component
    {
    public:
        void OnGUI() override;

        void SetBoss(BossComponent* _boss);

    private:
        BossComponent* boss = nullptr;
    };
}