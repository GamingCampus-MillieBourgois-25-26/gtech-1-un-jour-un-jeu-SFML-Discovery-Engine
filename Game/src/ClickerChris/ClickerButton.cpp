#include "ClickerChris/ClickerButton.h"
#include "Modules/InputModule.h"


void ClickerButton::SetController(ClickerController* controller) {
	this->controller = controller;
}
void ClickerButton::Update(float _delta_time)
{
    if (!controller) return;

    auto mouse = InputModule::GetMousePosition();

    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left) &&
        mouse.x >= position.x &&
        mouse.x <= position.x + size.x &&
        mouse.y >= position.y &&
        mouse.y <= position.y + size.y)
    {
        controller->AddScore();
    }
}