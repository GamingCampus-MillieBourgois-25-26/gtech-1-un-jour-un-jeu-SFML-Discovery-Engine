#pragma once
#include "Core/Component.h"


class ClickerController : public Component
{
public: 
	void AddScore();
	int GetScore() const;
	void OnGUI() override;

private:
	int score = 0;
	int scorePerClick = 1;
};

