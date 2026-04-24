#pragma once

#include "Core/Component.h"
#include "TextRenderer.h"

class FloatingTextComponent : public Component
{
public:
    void Start() override;
    void Update(float deltaTime) override;

    void Init(const std::string& text);

private:
    TextRenderer* textRenderer = nullptr;
    float lifetime = 1.0f; // durée en secondes
    float speed = 50.f;    // vitesse vers le haut
};