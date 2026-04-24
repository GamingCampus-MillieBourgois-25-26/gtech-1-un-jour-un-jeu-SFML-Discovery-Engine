#include "Clicker/ClickerLevel.h"

Clicker::ClickerLevel::ClickerLevel() : Scene("TowerLevel")
{
	WindowModule* window_module = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
	window_module->SetSize({ 800, 800 });

	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	Texture* textureDonut_Base = assets_module->LoadAsset<Texture>("Clicker/donut_base.png");
	Texture* textureDonut_Brown = assets_module->LoadAsset<Texture>("Clicker/donut_brown.png");
	Texture* textureDonut_Black = assets_module->LoadAsset<Texture>("Clicker/donut_black.png");
	Texture* textureGlazing_Green = assets_module->LoadAsset<Texture>("Clicker/green_glazing.png");

	GameObject* donut = CreateGameObject("Donut");
	float spriteSize = 264.f;

	donut->CreateComponent<SpriteRenderer>(textureDonut_Base);
	donut->SetScale({ 0.5f, 0.5f });
	donut->SetPosition({ 400.f - (spriteSize / 1.5f), 400.f - (spriteSize / 1.5f) });
	donut->CreateComponent<Donut>();
	donut->CreateComponent<Upgrade>();
	donut->GetComponent<SquareCollider>();

	GameObject* brownDonut = CreateGameObject("brownDonut");
	brownDonut->CreateComponent<SpriteRenderer>(textureDonut_Brown);
	brownDonut->CreateComponent<ShopUpgrade>("DonutBrown");
	brownDonut->SetScale({ 0.2f, 0.2f });
	brownDonut->SetPosition({ 150.f - (spriteSize / 1.8f), 150.f - (spriteSize / 1.8f) });

	GameObject* blackDonut = CreateGameObject("blackDonut");
	blackDonut->CreateComponent<SpriteRenderer>(textureDonut_Black);
	blackDonut->CreateComponent<ShopUpgrade>("DonutBlack");
	blackDonut->SetScale({ 0.2f, 0.2f });
	blackDonut->SetPosition({ 150.f + 60.f * 1 - (spriteSize / 1.8f), 150.f - (spriteSize / 1.8f) });

	GameObject* greenGlazing = CreateGameObject("greenGlazing");
	greenGlazing->CreateComponent<SpriteRenderer>(textureGlazing_Green);
	greenGlazing->CreateComponent<ShopUpgrade>("greenGlazing");
	greenGlazing->SetScale({ 0.2f, 0.2f });
	greenGlazing->SetPosition({ 150.f + 60.f * 2 - (spriteSize / 1.8f), 150.f - (spriteSize / 1.8f) });

	GameObject* greenGlazingDonut = CreateGameObject("greenGlazingDonut");
	greenGlazingDonut->CreateComponent<SpriteRenderer>(textureGlazing_Green);
	greenGlazingDonut->SetScale({ 0.5f, 0.5f });
	greenGlazingDonut->SetPosition({ 1000.f, 1000.f });

	GameObject* score = CreateGameObject("Score");
	score->CreateComponent<Score>(0);
}