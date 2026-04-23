#pragma once

#include "Core/Component.h"

class GameManagerComponent : public Component
{
public:
    static int baseHP;
    static int enemiesKilled;
    static int enemiesEscaped;

    static bool gameOver;
    static bool victory;

    void OnGUI() override;
};