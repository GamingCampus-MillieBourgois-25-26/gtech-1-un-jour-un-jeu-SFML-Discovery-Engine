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
	TextRenderer* text = GetOwner()->GetComponent<TextRenderer>();
	text->SetText("Carres: " + *nb);
}