#include "Pink.h"

Pink::Pink(InputModule* inpu, unsigned int* scor)
{
	score = scor;
	input = inpu;
}

void Pink::Update(float _delta_time)
{
	timer -= _delta_time;
	if (IsUnderCursor() && input->GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		if (*score >= cost)
		{
			level++;
			*score -= cost;
			cost *= 1.5f;
		}

	}
	if (timer <= 0)
	{
		*score += 2 * level;
		timer = 1.f;
	}
}

bool Pink::IsUnderCursor()
{
	const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

	Maths::Vector2f position = GetOwner()->GetPosition();
	position.x -= size / 2;
	position.y -= size / 2;
	const Maths::Vector2f& sizev = { size, size };

	const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(sizev));

	return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}