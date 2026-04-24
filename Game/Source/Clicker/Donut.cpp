#include "Clicker/Donut.h"

void Clicker::Donut::Update(float _delta_time)
{
	int mousePositionX = InputModule::GetMousePosition().x;
	int mousePositionY = InputModule::GetMousePosition().y;
	auto leftClickPressed = InputModule::GetMouseButtonDown(sf::Mouse::Button::Left);
	bool isMouseHoverDonut = mousePositionX >= 300.f && mousePositionX <= 475.f && mousePositionY >= 300.f && mousePositionY <= 475.f;

	if (leftClickPressed && isMouseHoverDonut)
	{
		isClicked = true;
	}
}

bool& Clicker::Donut::GetIsClicked()
{
	return isClicked;
}

void Clicker::Donut::ToggleIsClicked()
{
	isClicked = !isClicked;
}

//void Clicker::Donut::TestUpgrade()
//{
//	// Condition à utiliser et modifier :
//	// leftClickPressed && mousePositionX >= 300.f && mousePositionX <= 475.f && mousePositionY >= 300.f && mousePositionY <= 475.f
//	if (InputModule::GetKeyDown(sf::Keyboard::Key::A)) 
//	{
//		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
//		Texture* texture = assets_module->GetAsset<Texture>("Clicker/donut_brown.png");
//		GetOwner()->RemoveComponent(GetOwner()->GetComponent<SpriteRenderer>());
//		GetOwner()->CreateComponent<SpriteRenderer>(texture);
//
//		GetOwner()->GetComponent<Upgrade>()->DonutTypeUpgrade(0);
//	}
//}
