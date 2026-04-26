#include "Clicker/ClickerLevel.h"
#include <TextRenderer.h>

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
	donut->SetPosition({ 400.f - (spriteSize / 2.5f), 400.f - (spriteSize / 2.5f) });
	donut->SetScale({ 0.5f, 0.5f });
	donut->CreateComponent<Donut>();
	donut->CreateComponent<Upgrade>();

	GameObject* brownDonut = CreateGameObject("brownDonut");
	brownDonut->CreateComponent<SpriteRenderer>(textureDonut_Brown);
	brownDonut->CreateComponent<ShopUpgrade>("DonutBrown");
	brownDonut->SetScale({ 0.2f, 0.2f });
	brownDonut->SetPosition({ 120.f - (spriteSize / 2.8f), 120.f - (spriteSize / 2.8f) });

	GameObject* blackDonut = CreateGameObject("blackDonut");
	blackDonut->CreateComponent<SpriteRenderer>(textureDonut_Black);
	blackDonut->CreateComponent<ShopUpgrade>("DonutBlack");
	blackDonut->SetScale({ 0.2f, 0.2f });
	blackDonut->SetPosition({ 120.f + 60.f * 1 - (spriteSize / 2.8f), 120.f - (spriteSize / 2.8f) });

	GameObject* greenGlazing = CreateGameObject("greenGlazing");
	greenGlazing->CreateComponent<SpriteRenderer>(textureGlazing_Green);
	greenGlazing->CreateComponent<ShopUpgrade>("greenGlazing");
	greenGlazing->SetScale({ 0.2f, 0.2f });
	greenGlazing->SetPosition({ 120.f + 60.f * 2 - (spriteSize / 2.8f), 120.f - (spriteSize / 2.8f) });

	GameObject* greenGlazingDonut = CreateGameObject("greenGlazingDonut");
	greenGlazingDonut->CreateComponent<SpriteRenderer>(textureGlazing_Green);
	greenGlazingDonut->SetScale({ 0.5f, 0.5f });
	greenGlazingDonut->SetPosition({ 1000.f, 1000.f });

	GameObject* score = CreateGameObject("Score");
	score->CreateComponent<Score>(0);
	score->CreateComponent<TextRenderer>("Engine/Inter-VariableFont_opsz,wght.ttf");
	score->GetComponent<TextRenderer>()->SetCharacterSize(24);
	score->GetComponent<TextRenderer>()->SetText("Points : 0");
	score->GetComponent<TextRenderer>()->SetColor(sf::Color::White);
	score->SetPosition({ donut->GetPosition().x - 100.f, donut->GetPosition().y - 100.f });
}