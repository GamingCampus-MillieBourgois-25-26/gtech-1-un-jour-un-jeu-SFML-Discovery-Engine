#pragma once
#include "Core/Component.h"

enum class ButtonTarget { TowerDefense, BulletHell };

class ButtonComponent : public Component
{
public:
    void Update(float dt) override;
    void OnClick();

    ButtonTarget target = ButtonTarget::TowerDefense;

    sf::FloatRect bounds;
};