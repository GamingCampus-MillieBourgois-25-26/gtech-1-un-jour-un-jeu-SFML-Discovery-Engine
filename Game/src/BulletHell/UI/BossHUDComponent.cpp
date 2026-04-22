#include "BulletHell/UI/BossHUDComponent.h"

#include "imgui.h"

#include "BulletHell/Components/BossComponent.h"

namespace bulletHell
{
    void BossHUDComponent::OnGUI()
    {
        if (boss == nullptr)
        {
            return;
        }

        if (!ImGui::Begin("Boss HUD"))
        {
            ImGui::End();
            return;
        }

        const float currentHealth = boss->GetCurrentHealth();
        const float maxHealth = boss->GetMaxHealth();
        const float ratio = (maxHealth > 0.0f) ? (currentHealth / maxHealth) : 0.0f;

        ImGui::Text("Boss Phase: %d", boss->GetPhase());
        ImGui::Text("Boss HP: %.0f / %.0f", currentHealth, maxHealth);
        ImGui::ProgressBar(ratio, ImVec2(320.0f, 20.0f));

        if (boss->IsDefeated())
        {
            ImGui::Separator();
            ImGui::Text("VICTORY");
        }

        ImGui::End();
    }

    void BossHUDComponent::SetBoss(BossComponent* _boss)
    {
        boss = _boss;
    }
}