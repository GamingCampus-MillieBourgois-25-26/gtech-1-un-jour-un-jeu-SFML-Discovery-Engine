#pragma once

#include "Core/Component.h"

class TextRenderer;

class ClickComponent : public Component
{
public:
    void Update(float deltaTime) override;

    static TextRenderer* scoreText; // 🔥 global

private:
    int score = 0;
    bool canClick = true;

    float currentScale = 1.f;
    float targetScale = 1.f;
};