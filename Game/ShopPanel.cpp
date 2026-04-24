#include "ShopPanel.h"

void ShopPanel::Start()
{
    rectangle = GetOwner()->CreateComponent<RectangleShapeRenderer>();
    rectangle->SetSize({ 300.f, 600.f });
    rectangle->SetColor(sf::Color::Red);

    GetOwner()->SetPosition({ 700.f, 0.f });
}