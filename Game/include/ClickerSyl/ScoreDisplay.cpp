#include "ScoreDisplay.h"
#include "Components/TextRenderer.h"
#include "Components/RectangleShapeRenderer.h"
#include <iostream>

ScoreDisplay::ScoreDisplay(unsigned int* scor, std::string* n)
{
	score = scor;
	nb = n;
}

void ScoreDisplay::Update(float _delta_time)
{
	*nb = std::to_string(*score);
	RectangleShapeRenderer* shape = GetOwner()->CreateComponent<RectangleShapeRenderer>();
	shape->SetColor(sf::Color::Black);
	shape->SetSize(Maths::Vector2f(400.f, 50.f));
	TextRenderer* text = GetOwner()->CreateComponent<TextRenderer>("Carres: " + *nb);
	text->SetColor(sf::Color::Yellow);
}