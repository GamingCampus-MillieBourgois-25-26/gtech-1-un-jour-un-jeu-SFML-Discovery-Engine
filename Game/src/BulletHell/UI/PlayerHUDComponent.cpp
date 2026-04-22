#include "BulletHell/UI/PlayerHUDComponent.h"

#include "imgui.h"

#include "BulletHell/BulletHellDebug.h"
#include "BulletHell/Components/PlayerController.h"

namespace bulletHell
{
    void PlayerHUDComponent::OnGUI()
    {
        if (!g_showDebugUI)
        {
            return;
        }

        if (player == nullptr)
        {
            return;
        }

        if (!ImGui::Begin("Player HUD"))
        {
            ImGui::End();
            return;
        }

        ImGui::Text("Lives: %d", player->GetLives());

        if (player->IsDead())
        {
            ImGui::Separator();
            ImGui::Text("GAME OVER");
        }

        ImGui::End();
    }

    void PlayerHUDComponent::SetPlayer(PlayerController* _player)
    {
        player = _player;
    }
}