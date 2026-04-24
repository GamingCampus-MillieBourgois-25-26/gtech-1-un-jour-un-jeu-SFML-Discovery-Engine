#pragma once
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Modules/WindowModule.h"
#include "Modules/AssetsModule.h"
#include "Modules/InputModule.h"
#include "ClickerSyl/Square.h"

class ClickerScene final : public Scene
{
public:
	ClickerScene() : Scene("Clicker")
	{
		input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
		window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
		// load textures
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* squareTex = assets_module->LoadAsset<Texture>("Sylvain/Clicker/square.png");

		//window size
		Maths::Vector2u window_size = window->GetSize();

		GameObject* square = CreateGameObject("square");
		square->CreateComponent<Square>(input, window);
		square->SetPosition({ (float)window_size.x / 2, (float)window_size.y / 2});
		square->CreateComponent<SpriteRenderer>(squareTex);
	}

	InputModule* input;
	WindowModule* window;
};

