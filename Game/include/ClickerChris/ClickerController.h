#pragma once
#include "Core/Component.h"


class ClickerController : public Component
{
public: 
	void AddScore();
	int GetScore() const;
	void OnGUI() override;
	void BuyUpgrade();
	int GetScorePerClick() const;
	int GetUpgradeCost() const;
	void AutoClicker();
	void BuyAutoClicker();
	void Update(float _delta_time) override;

private:
	int score = 0;
	int scorePerClick = 1;
	int upgradeCost = 10;
	int inflation = 1;
	int autoClickerCount = 0;
	int autoClickerCost = 50;
	float autoClickerTimer = 0.f;

};

