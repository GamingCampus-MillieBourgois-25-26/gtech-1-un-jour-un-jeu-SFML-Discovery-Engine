#include "TowerSelection.h"
#include "InputModule.h"

TowerSelection::TowerSelection(RectangleShapeRenderer* shap, SelectedTower* select, Type TowerType)
{
	shape = shap;
    selector = select;
    type = TowerType;
}

void TowerSelection::Update(float _delta_time)
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

bool TowerSelection::IsUnderCursor()
{
    const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

    Maths::Vector2f position = GetOwner()->GetPosition();
    position -= {30.f, 30.f};
    const Maths::Vector2f& size = shape->GetSize() / 2;

    const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size));

    return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}