#include "Clicker/ShopUpgrade.h"

Clicker::ShopUpgrade::ShopUpgrade(std::string _typeUpgrade)
{
	typeUpgrade = _typeUpgrade;
}

void Clicker::ShopUpgrade::Start()
{
	assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
}

void Clicker::ShopUpgrade::Update(float _delta_time)
{
	leftClickPressed = InputModule::GetMouseButtonDown(sf::Mouse::Button::Left);
	mousePositionX = InputModule::GetMousePosition().x;
	mousePositionY = InputModule::GetMousePosition().y;

	BuyUpgrade(typeUpgrade);
}

void Clicker::ShopUpgrade::BuyUpgrade(std::string typeUpgrade) 
{
	// Upgrade : Brown Donut
	bool hoverDonutBrown = mousePositionX >= 0.f && mousePositionX <= 75.f && mousePositionY >= 0.f && mousePositionY <= 75.f;
	if (leftClickPressed && typeUpgrade == "DonutBrown" && hoverDonutBrown)
	{
		Logger::Log(ELogLevel::Info, "Upgrade : DonutBrown");
		Texture* texture = assets_module->GetAsset<Texture>("Clicker/donut_brown.png");
		// GetOwner()->RemoveComponent(GetOwner()->GetComponent<SpriteRenderer>());
		GetOwner()->CreateComponent<SpriteRenderer>(texture);

		GetOwner()->GetScene()->FindGameObject("Donut")->GetComponent<Upgrade>()->SetDonutTypeUpgrade(0);
	}

	// Upgrade : Black Donut
	bool hoverDonutBlack = mousePositionX >= 80.f && mousePositionX <= 150.f && mousePositionY >= 0.f && mousePositionY <= 75.f;
	if (leftClickPressed && typeUpgrade == "DonutBlack" && hoverDonutBlack)
	{
		Logger::Log(ELogLevel::Info, "Upgrade : DonutBlack");
		GameObject* donut = GetOwner()->GetScene()->FindGameObject("Donut");
		Texture* texture = assets_module->GetAsset<Texture>("Clicker/donut_black.png");

		// donut->RemoveComponent(GetOwner()->GetComponent<SpriteRenderer>());
		donut->CreateComponent<SpriteRenderer>(texture);

		GetOwner()->GetScene()->FindGameObject("Donut")->GetComponent<Upgrade>()->SetDonutTypeUpgrade(1);
	}

	// Upgrade : Green Glazing 
	bool hoverGreenGlazing = mousePositionX >= 160.f && mousePositionX <= 225.f && mousePositionY >= 0.f && mousePositionY <= 75.f;
	if (leftClickPressed && typeUpgrade == "greenGlazing" && hoverGreenGlazing)
	{
		Logger::Log(ELogLevel::Info, "Upgrade : GreenGlazing");
		float spriteSize = 226.f;

		GameObject* donut = GetOwner()->GetScene()->FindGameObject("Donut");
		GameObject* glazingGreen = GetOwner()->GetScene()->FindGameObject("greenGlazingDonut");
		glazingGreen->SetPosition({ 385.f - (spriteSize / 1.5f), 385.f - (spriteSize / 1.5f) });

		donut->GetComponent<Upgrade>()->SetGlazingTypeUpgrade(2);
	}
}