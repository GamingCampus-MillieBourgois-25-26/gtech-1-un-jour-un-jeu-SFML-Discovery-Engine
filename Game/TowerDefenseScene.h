#pragma once
#include "Core/Scene.h"

class TowerDefenseScene final : public Scene
{
public:
    // Le constructeur doit être identique en structure à BulletHellScene
    TowerDefenseScene() : Scene("TowerDefense", false)
    {
        // On laisse vide pour l'instant, mais la structure est là
    }
};