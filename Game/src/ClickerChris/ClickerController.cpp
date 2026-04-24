#include "ClickerChris/ClickerController.h"
#include "imgui.h"


	void ClickerController::AddScore() {
		score += scorePerClick;
	}

	int ClickerController::GetScore() const{
		return score;
	}
	int ClickerController::GetScorePerClick() const {
		return scorePerClick;
	}

	int ClickerController::GetUpgradeCost() const{
		return upgradeCost;
	}


	void ClickerController::OnGUI() {
		ImGui::Begin("Clicker");
		ImGui::Text("Score : %d", score);
		ImGui::Text("ScorePerClick : %d", scorePerClick);
		ImGui::Text("Upgrade Cost : %d", upgradeCost);
		ImGui::Text("AutoClikerCount : %d", autoClickerCount);
		ImGui::Text("AutoClikerCost : %d", autoClickerCost);
		
		if (ImGui::Button("Upgrade"))
		{
			BuyUpgrade();
		}
		
		if (ImGui::Button("Buy AutoClicker "))
		{
			BuyAutoClicker();
		}
		
		ImGui::End();
	}

	void ClickerController::BuyUpgrade()
	{
		if (score >= upgradeCost)
		{
			score -= upgradeCost;
			scorePerClick += 1 + inflation / 2;
			upgradeCost += 10 * inflation;
			inflation += 1;
		}
	}
	
	void ClickerController::BuyAutoClicker()
	{
		if (score >= autoClickerCost)
		{
			score -= autoClickerCost;
			autoClickerCount += 1;
			autoClickerCost += 50 + 25 * autoClickerCount;
		}
	}

	void ClickerController::Update(float _delta_time) {
		if (autoClickerCount > 0) {
			autoClickerTimer += _delta_time;

			if (autoClickerTimer >= 1.f) {
				score += autoClickerCount;
				autoClickerTimer = 0.f;
			}
		}
	}