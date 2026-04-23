#include "TowerDefenseChris/GameManagerComponent.h"

#include <imgui.h>

int GameManagerComponent::baseHP = 3;
int GameManagerComponent::enemiesKilled = 0;
int GameManagerComponent::enemiesEscaped = 0;

bool GameManagerComponent::gameOver = false;
bool GameManagerComponent::victory = false;

void GameManagerComponent::OnGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10.f, 10.f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.75f);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("HUD", nullptr, flags);

    ImGui::Text("HP: %d", baseHP);
    ImGui::Text("Kills: %d", enemiesKilled);
    ImGui::Text("Escaped: %d", enemiesEscaped);

    if (gameOver)
        ImGui::Text("GAME OVER");

    if (victory)
        ImGui::Text("VICTORY");

    ImGui::End();
}