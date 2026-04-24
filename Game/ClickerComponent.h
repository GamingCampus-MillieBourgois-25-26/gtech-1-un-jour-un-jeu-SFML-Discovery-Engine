#pragma once
#include "Core/Component.h"
#include <SFML/Graphics.hpp>

class ClickerComponent : public Component
{
public:
    void Update(float dt) override;

    // Statistiques
    long long score = 0;
    int pointsPerClick = 1;

private:

    bool wasMouseButtonPressed = false;
};