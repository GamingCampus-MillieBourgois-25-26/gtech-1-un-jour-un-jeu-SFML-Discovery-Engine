#include "pch.h"
#include "EndGame.h"
#include "Core/Scene.h"
#include "Modules/WindowModule.h"
#include <string>

void EndGame::End(bool end)
{
	if (display == nullptr)
	{
		std::string string;
		sf::Color color;
		Maths::Vector2f pos = {140.f, 90.f};
		Maths::Vector2u window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();
		if (end)
		{
			string = "Victory !";
			color = sf::Color::Green;
			pos.x = 100.f;
		}
		else
		{
			string = "Game Over";
			color = sf::Color::Red;
		}
		display = GetOwner()->GetScene()->CreateGameObject("displayEnd");
		display->SetPosition({ window.x / 2 - pos.x, window.y / 2 - pos.y});
		TextRenderer* text = display->CreateComponent<TextRenderer>(string);
		text->SetColor(color);
		text->SetCharacterSize(60);
	}
}
