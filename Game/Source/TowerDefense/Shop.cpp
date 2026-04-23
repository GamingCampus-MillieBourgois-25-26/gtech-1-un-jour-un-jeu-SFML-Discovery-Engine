#include "TowerDefense/Shop.h"

TowerDefense::Shop::Shop(sf::Vector2f _position)
{
	position = _position;
}

void TowerDefense::Shop::Start()
{
	GetOwner()->SetPosition({ position.x, position.y });
	GetOwner()->SetScale({ 0.5f, 0.5f });
}

void TowerDefense::Shop::Update(float _delta_time)
{
	int mousePositionX = InputModule::GetMousePosition().x;
	int mousePositionY = InputModule::GetMousePosition().y;
	auto leftClickPressed = InputModule::GetMouseButtonDown(sf::Mouse::Button::Left);

	// 1ère case du shop
	if (leftClickPressed && mousePositionX >= 0.f && mousePositionX <= 50.f && mousePositionY >= 550.f && mousePositionY <= 600.f)
	{
		if (GetOwner()->GetName() == "Tour_Simple")
		{
			Logger::Log(ELogLevel::Info, "Tour simple achete");
		}
	}

	// 2ème case du shop
	if (leftClickPressed && mousePositionX >= 50.f && mousePositionX <= 100.f && mousePositionY >= 550.f && mousePositionY <= 600.f)
	{
		if (GetOwner()->GetName() == "Tour_Double")
		{
			Logger::Log(ELogLevel::Info, "Tour double achete");
		}
	}

	// 3ème case du shop
	if (leftClickPressed && mousePositionX >= 100.f && mousePositionX <= 150.f && mousePositionY >= 550.f && mousePositionY <= 600.f)
	{
		if (GetOwner()->GetName() == "Mur")
		{
			Logger::Log(ELogLevel::Info, "Mur achete");
		}
	}
}
