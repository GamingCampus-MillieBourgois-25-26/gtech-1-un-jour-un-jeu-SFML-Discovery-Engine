#include "FloatingTextComponent.h"
#include "GameObject.h"

void FloatingTextComponent::Start()
{
    textRenderer = GetOwner()->CreateComponent<TextRenderer>("+1");
    textRenderer->SetColor(sf::Color::Yellow);
}

void FloatingTextComponent::Init(const std::string& text)
{
    if (textRenderer)
        textRenderer->SetText(text);
}

void FloatingTextComponent::Update(float deltaTime)
{
    // mouvement vers le haut
    auto pos = GetOwner()->GetPosition();
    pos.y -= speed * deltaTime;
    GetOwner()->SetPosition(pos);

    // durée de vie
    lifetime -= deltaTime;

    if (lifetime <= 0.f)
    {
        GetOwner()->MarkForDeletion();
    }
}