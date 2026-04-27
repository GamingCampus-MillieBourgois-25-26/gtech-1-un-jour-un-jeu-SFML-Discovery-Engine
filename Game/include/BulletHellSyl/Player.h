#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Components/TextRenderer.h"

class Player : public Component
{
public:
    Player();
    void Update(const float _delta_time) override;
    bool CheckCollision();
    void UpdateDisplayer();
    void CreateDisplayer();

    float speed = 200.0f;
    Maths::Vector2u window_size;
    int life = 3;
    GameObject* lifeDisplayer = nullptr;
    float invunerabilityTime = 1.f;
};
