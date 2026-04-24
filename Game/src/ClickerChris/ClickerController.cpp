	#include "ClickerChris/ClickerController.h"
	#include "imgui.h"


	void ClickerController::AddScore() {
		score += scorePerClick;
	}

	int ClickerController::GetScore() const{
		return score;
	}

	void ClickerController::OnGUI() {
		ImGui::Begin("Clicker");
		ImGui::Text("Score : %d", score);
		ImGui::End();
	}

