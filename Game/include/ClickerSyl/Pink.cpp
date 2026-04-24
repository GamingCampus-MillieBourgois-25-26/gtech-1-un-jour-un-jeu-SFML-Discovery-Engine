#include "Pink.h"
#include <iostream>

Pink::Pink(InputModule* inpu, WindowModule* windo)
{
	window = windo;
	input = inpu;
	//GetOwner()->SetPosition({ (float)window->GetSize().x, (float)size / 2 });
}

void Pink::Update(float _delta_time)
{
	if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		if (IsUnderCursor())
		{
			std::cout << "pink: " << std::endl;
		}
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