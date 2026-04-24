#pragma once

#include "Scene.h"

class MainScene : public Scene
{
public:
    MainScene() : Scene("MainScene") {}

    void Start() const;                 // ✅ signature correcte
    void Update(float deltaTime) const; // ✅ signature correcte

private:
    mutable int points = 0; // ⚠️ obligatoire car fonctions const
};