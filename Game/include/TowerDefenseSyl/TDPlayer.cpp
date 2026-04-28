#include "TDPlayer.h"

void TDPlayer::Update(float _delta_time)
{
	std::string string = std::to_string(gold);
	TextRenderer* text = GetOwner()->GetComponent<TextRenderer>();
	text->SetText("gold: " + string);
}

int* TDPlayer::GetGold()
{
	return &gold;
}