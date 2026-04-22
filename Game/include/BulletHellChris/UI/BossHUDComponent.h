#pragma once

#include "Core/GameObject.h"

namespace bulletHell
{
    class BossComponent;

    class BossHUDComponent final : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;

        void SetBoss(BossComponent* _boss);
        void SetBarBackground(GameObject* _barBackground);
        void SetBarFill(GameObject* _barFill);

    private:
        void RefreshBar();

    private:
        BossComponent* boss = nullptr;
        GameObject* barBackground = nullptr;
        GameObject* barFill = nullptr;

        float maxBarWidth = 300.0f;
        float barHeight = 10.0f;
    };
}