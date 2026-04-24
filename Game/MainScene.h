#pragma once

#include "Core/Scene.h"

class MainScene : public Scene
{
public:
    MainScene();

    void Update(float deltaTime) const; 

private:
    mutable int points = 0;
    mutable bool canClick = true;
};