#include "Square.h"
#include "ClickerDisplay.h"
#include "Core/Scene.h"
#include <iostream>
#include "Components/RectangleShapeRenderer.h"
#include "Components/TextRenderer.h"

Square::Square(InputModule* inpu, WindowModule* windo, unsigned int* scor, unsigned int* clic)
{
	window = windo;
	input = inpu;
	score = scor;
	click = clic;
}

void Square::Update(float _delta_time)
{
	if (IsUnderCursor())
	{
		if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			*score += *click;
			std::string string = std::to_string(*click);
			GameObject* clickDisplay = GetOwner()->GetScene()->CreateGameObject("display");
			clickDisplay->SetPosition(static_cast<Maths::Vector2f>(InputModule::GetMousePosition()));
			clickDisplay->CreateComponent<ClickerDisplay>();
			TextRenderer* test = clickDisplay->CreateComponent<TextRenderer>("+" + string);
			test->SetColor(sf::Color::White);
		}
		if (input->GetMouseButton(sf::Mouse::Button::Left))
			GetOwner()->SetScale({ 1.1f, 1.1f });
		else
		{
			GetOwner()->SetScale({ 1.f, 1.f });
		}
	}
}

bool Square::IsUnderCursor()
{
	const Maths::Vector2f mouse_position = static_cast<Maths::Vector2f>(InputModule::GetMousePosition());

	Maths::Vector2f position = GetOwner()->GetPosition();
	position.x -= size / 2;
	position.y -= size / 2;
	const Maths::Vector2f& sizev = { size, size };

	const sf::Rect<float> tile_rect = sf::Rect(static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(sizev));

	return tile_rect.contains(static_cast<sf::Vector2f>(mouse_position));
}