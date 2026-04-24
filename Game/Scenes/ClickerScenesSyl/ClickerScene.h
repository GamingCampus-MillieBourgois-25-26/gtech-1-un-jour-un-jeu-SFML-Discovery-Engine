#pragma once
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Modules/WindowModule.h"
#include "Modules/AssetsModule.h"
#include "Modules/InputModule.h"
#include "ClickerSyl/Square.h"
#include "Components/TextRenderer.h"
#include "ClickerSyl/Cursor.h"
#include "ClickerSyl/Pink.h"
#include "ClickerSyl/ScoreDisplay.h"
#include "ClickerSyl/PriceDisplay.h"

class ClickerScene final : public Scene
{
public:
	ClickerScene() : Scene("Clicker")
	{
		input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
		window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		// load textures
		Texture* cursorTex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/cursor.png");
		Texture* squareTex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/square.png");
		Texture* pinkTex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/pink.png");
		Texture* faceATex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/face_a.png");
		Texture* faceBTex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/face_b.png");

		//window size
		Maths::Vector2u window_size = window->GetSize();

		//GameObjects
		GameObject* square = CreateGameObject("square");
		square->CreateComponent<Square>(input, window, &score, &click);
		square->SetPosition({ (float)window_size.x / 3.5f, (float)window_size.y / 2});
		square->CreateComponent<SpriteRenderer>(squareTex);
		square->CreateComponent<SpriteRenderer>(faceATex);

		GameObject* cursor = CreateGameObject("cursor");
		cursor->SetScale({ 3.f, 3.f });
		cursor->SetPosition({ (float)window_size.x - 130.f , 100.f });
		Cursor* cursorComp = cursor->CreateComponent<Cursor>(input, window, &score, &click);
		cursor->CreateComponent<SpriteRenderer>(cursorTex);

		GameObject* pink = CreateGameObject("pink");
		pink->SetPosition({ (float)window_size.x - 130.f , 220.f });
		Pink* pinkComp = pink->CreateComponent<Pink>(input, &score);
		pink->CreateComponent<SpriteRenderer>(pinkTex);
		pink->CreateComponent<SpriteRenderer>(faceBTex);

		GameObject* upgrade = CreateGameObject("display");
		upgrade->SetPosition({ (float)window_size.x - 200.f , 10.f });
		TextRenderer* text = upgrade->CreateComponent<TextRenderer>("Upgrades");
		text->SetColor(sf::Color::Green);

		GameObject* display = CreateGameObject("display");
		display->CreateComponent<ScoreDisplay>(&score, &nb);

		GameObject* cursorPrice = CreateGameObject("display");
		cursorPrice->SetPosition({ (float)window_size.x - 200.f , 120.f });
		cursorPrice->CreateComponent<PriceDisplay>(&cursorComp->cost);

		GameObject* pinkPrice = CreateGameObject("display");
		pinkPrice->SetPosition({ (float)window_size.x - 200.f , 270.f });
		pinkPrice->CreateComponent<PriceDisplay>(&pinkComp->cost);
	}

	unsigned int score = 0;
	unsigned int click = 1;
	std::string nb = std::to_string(score);
	InputModule* input;
	WindowModule* window;
};

