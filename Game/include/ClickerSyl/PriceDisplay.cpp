#include "PriceDisplay.h"
#include "Core/GameObject.h"
#include "Components/TextRenderer.h"
#include "Components/RectangleShapeRenderer.h"
#include <string>

PriceDisplay::PriceDisplay(unsigned int* pric)
{
	price = pric;
}

void PriceDisplay::Update(float _delta_time)
{
	std::string priceString = std::to_string(*price);
	RectangleShapeRenderer* shape = GetOwner()->CreateComponent<RectangleShapeRenderer>();
	shape->SetColor(sf::Color::Black);
	shape->SetSize(Maths::Vector2f(250.f, 50.f));
	TextRenderer* text = GetOwner()->CreateComponent<TextRenderer>(priceString + " Carres");
	text->SetColor(sf::Color::White);
	text->SetCharacterSize(25);
}