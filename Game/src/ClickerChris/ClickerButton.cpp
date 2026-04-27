#include "ClickerChris/ClickerButton.h"
#include "Modules/InputModule.h"


void ClickerButton::SetController(ClickerController* controller) {
	this->controller = controller;
}
void ClickerButton::Update(float _delta_time)
{
    if (!controller) return;

    auto mouse = InputModule::GetMousePosition();
    auto position = GetOwner()->GetPosition();


    bool isHover =
        mouse.x >= position.x - size.x * 0.5f &&
        mouse.x <= position.x + size.x * 0.5f &&
        mouse.y >= position.y - size.y * 0.5f &&
        mouse.y <= position.y + size.y * 0.5f;

    if (isHover && InputModule::GetMouseButton(sf::Mouse::Button::Left))
    {
        GetOwner()->SetScale(Maths::Vector2f(3.8f, 3.8f));

    }
    else if (isHover)
    {
        GetOwner()->SetScale(Maths::Vector2f(4.2f, 4.2f));
    }
    else
    {
        GetOwner()->SetScale(Maths::Vector2f(4.f, 4.f));
    }

    if (isHover && InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        controller->AddScore();
    }
}