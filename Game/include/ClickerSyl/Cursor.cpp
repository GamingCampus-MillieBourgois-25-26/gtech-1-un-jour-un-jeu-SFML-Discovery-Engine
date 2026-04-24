#include "Cursor.h"
#include "Components/TextRenderer.h"
#include "Components/RectangleShapeRenderer.h"
#include <iostream>

Cursor::Cursor(InputModule* inpu, WindowModule* windo, unsigned int* scor, unsigned int* clic)
{
	window = windo;
	input = inpu;
	score = scor;
	click = clic;
}

void Cursor::Update(float _delta_time)
{
	if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		if (IsUnderCursor())
		{
			if (*score >= cost)
			{
				*score -= cost;
				*click += 1;
				float newCost = cost * 1.5f;
				cost = newCost;
				std::cout << "clic +1" << std::endl;
			}
		}
	}
}

bool Cursor::IsUnderCursor()
{
	const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

	Maths::Vector2f position = GetOwner()->GetPosition();
	position.x -= size / 2;
	position.y -= size / 2;
	const Maths::Vector2f& sizev = { size, size };

	const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(sizev));

	return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}