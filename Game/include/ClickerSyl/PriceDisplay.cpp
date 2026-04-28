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
	TextRenderer* text = GetOwner()->GetComponent<TextRenderer>();
	text->SetText(priceString + " Carres");
}