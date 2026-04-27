#pragma once
#include "Core/Component.h"

class Scene;

class InputTowerComponent : public Component
{
public:
    static Scene* scene;

    void Update(float _delta_time) override;
};