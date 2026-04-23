#pragma once
#include "Core/Component.h"

class Scene;

class SpawnerComponent : public Component
{
public:
    static Scene* scene;

    void Update(float _delta_time) override;

private:
    float timer = 0.f;
};