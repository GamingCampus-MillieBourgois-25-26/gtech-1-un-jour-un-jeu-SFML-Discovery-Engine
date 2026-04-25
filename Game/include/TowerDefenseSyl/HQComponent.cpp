#include "HQComponent.h"
#include "Components/TextRenderer.h"
#include "LifeDisplay.h"
#include "Core/Scene.h"
#include <string>

HQComponent::HQComponent()
{
}

void HQComponent::Update(float _delta_time)
{
	if (!init)
	{
		init = true;
		Init();
	}
}

void HQComponent::Init()
{
	std::string string = std::to_string(hp);
	life = GetOwner()->GetScene()->CreateGameObject("display");
	life->SetPosition({ 470.f , 400.f });
	life->CreateComponent<LifeDisplay>();
	TextRenderer* text = life->CreateComponent<TextRenderer>("life: " + string + "/3");
	text->SetColor(sf::Color::White);

}

void HQComponent::TakeDamage()
{
	life->MarkForDeletion();
	hp--;
	if (hp < 0)
		hp = 0;
	std::string string = std::to_string(hp);
	life = GetOwner()->GetScene()->CreateGameObject("display");
	life->SetPosition({ 470.f , 400.f });
	life->CreateComponent<LifeDisplay>();
	TextRenderer* text = life->CreateComponent<TextRenderer>("life: " + string + "/3");
	text->SetColor(sf::Color::White);
	if (hp == 0 && final == nullptr)
	{
		final = GetOwner()->GetScene()->CreateGameObject("display");
		final->SetPosition({ 200.f , 250.f });
		final->CreateComponent<LifeDisplay>();
		TextRenderer* text = final->CreateComponent<TextRenderer>("Perdu !");
		text->SetColor(sf::Color::Red);
	}
}