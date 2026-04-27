#include "TowerASelection.h"
#include "InputModule.h"

TowerASelection::TowerASelection(RectangleShapeRenderer* shap, SelectedTower* select)
{
	shape = shap;
    selector = select;
}

void TowerASelection::Update(float _delta_time)
{
    if (IsUnderCursor())
    {
        shape->SetColor(sf::Color::Green);
        if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
            selector->SetSelectedTower(&type);
    }
    else
        shape->SetColor(sf::Color::Transparent);
}

bool TowerASelection::IsUnderCursor()
{
    const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

    Maths::Vector2f position = GetOwner()->GetPosition();
    position -= {30.f, 30.f};
    const Maths::Vector2f& size = shape->GetSize() / 2;

    const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size));

    return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}