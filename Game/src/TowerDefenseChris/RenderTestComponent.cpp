#include "TowerDefenseChris/RenderTestComponent.h"

void RendererTestComponent::Start()
{
	rect.setSize({ 100.f, 100.f });
	rect.setFillColor(sf::Color::Red);
	rect.setPosition({ 300.f, 200.f });
}

void RendererTestComponent::Render(sf::RenderWindow* window) {
	window->draw(rect);

}