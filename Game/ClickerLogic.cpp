#include "ClickerLogic.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Modules/AssetsModule.h"
#include "Modules/InputModule.h"
#include "Modules/WindowModule.h"
#include "Components/SpriteRenderer.h"
#include <imgui.h>
#include <iostream>

void ClickerLogic::Update(float _dt)
{
    auto* mm = Engine::GetInstance()->GetModuleManager();
    auto* input = mm->GetModule<InputModule>();
    auto* windowMod = mm->GetModule<WindowModule>();

    if (!input || !windowMod) return;

    // --- 1. CLIC MANUEL (Inchangé) ---
    if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        if (can_Click)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*(windowMod->GetWindow()));
            sf::Vector2f worldPos = windowMod->GetWindow()->mapPixelToCoords(pixelPos);
            Maths::Vector2f pos = GetOwner()->GetPosition();

            if (worldPos.x >= pos.x - 32.0f && worldPos.x <= pos.x + 32.0f &&
                worldPos.y >= pos.y - 32.0f && worldPos.y <= pos.y + 32.0f)
            {
                m_money++;
                if (std::rand() % 75 == 0) m_gems++;
                GetOwner()->SetScale(Maths::Vector2f(1.15f, 1.15f));
            }
            can_Click = false;
        }
    }
    else
    {
        can_Click = true;
        Maths::Vector2f currentScale = GetOwner()->GetScale();
        if (currentScale.x > 1.0f)
        {
            float newScale = currentScale.x - (2.0f * _dt);
            if (newScale < 1.0f) newScale = 1.0f;
            GetOwner()->SetScale(Maths::Vector2f(newScale, newScale));
        }
    }

    // --- 2. LOGIQUE AUTO-COIN ---
    if (m_autoCoinCount > 0)
    {
        m_autoCoinTimer += _dt;
        if (m_autoCoinTimer >= m_autoCoinDelay)
        {
            m_money++;
            m_autoCoinTimer = 0.0f;
            m_iconDisplayTimer = 0.8f; // Temps d'affichage

            // Création UNIQUE de l'objet s'il n'existe pas
            if (!m_feedbackIcon)
            {
                auto* sm = mm->GetModule<SceneModule>();
                if (sm && !sm->GetScenesList().empty())
                {
                    Scene* currentScene = sm->GetScenesList().front().get();
                    m_feedbackIcon = currentScene->CreateGameObject("FeedbackCoin");

                    auto* assets = mm->GetModule<AssetsModule>();
                    Texture* tex = assets->GetAsset<Texture>("coin_06.png");
                    if (!tex) tex = assets->LoadAsset<Texture>("coin_06.png");

                    if (tex) {
                        m_iconRenderer = m_feedbackIcon->CreateComponent<SpriteRenderer>(tex);
                    }
                }
            }

            // Reset de l'animation
            if (m_feedbackIcon) {
                m_feedbackIcon->SetPosition(GetOwner()->GetPosition());
                m_feedbackIcon->SetScale(Maths::Vector2f(1.5f, 1.5f));
            }
        }
    }

    // --- 3. ANIMATION DE L'ICÔNE ---
    if (m_iconDisplayTimer > 0.0f)
    {
        m_iconDisplayTimer -= _dt;
        if (m_feedbackIcon) {
            // Monte vers le haut
            Maths::Vector2f p = m_feedbackIcon->GetPosition();
            m_feedbackIcon->SetPosition(Maths::Vector2f(p.x, p.y - (120.0f * _dt)));

            // Disparaît progressivement en rétrécissant
            float s = (m_iconDisplayTimer / 0.8f) * 1.5f;
            m_feedbackIcon->SetScale(Maths::Vector2f(s, s));
        }
    }
    else if (m_feedbackIcon && m_feedbackIcon->GetScale().x > 0.0f)
    {
        // On cache l'objet quand le timer est fini
        m_feedbackIcon->SetScale(Maths::Vector2f(0.0f, 0.0f));
    }
}

void ClickerLogic::OnGUI()
{
    float windowWidth = ImGui::GetIO().DisplaySize.x;

    // --- AFFICHAGE MONNAIES ---
    ImGui::SetNextWindowPos(ImVec2(windowWidth - 250, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(220, 120), ImGuiCond_Always);
    ImGui::Begin("CurrencyUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

    ImGui::SetWindowFontScale(2.5f);
    ImGui::TextColored(ImVec4(1.0f, 0.84f, 0.0f, 1.0f), "$ %d", m_money);
    ImGui::SetWindowFontScale(1.8f);
    ImGui::TextColored(ImVec4(0.0f, 0.9f, 1.0f, 1.0f), "Gem: %d", m_gems);
    ImGui::End();

    // --- BOUTIQUE ---
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(280, 180), ImGuiCond_Always);
    ImGui::Begin("UpgradesUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

    ImGui::Text("BOUTIQUE");
    ImGui::Separator();

    int currentPrice = (int)m_autoCoinPrice;
    std::string btnText = "Auto-Coin (" + std::to_string(currentPrice) + "$)";

    // Condition : Argent suffisant ET cooldown > 0.5s
    bool canBuy = (m_money >= currentPrice && m_autoCoinDelay > 0.5f);

    if (!canBuy) ImGui::BeginDisabled();
    if (ImGui::Button(btnText.c_str(), ImVec2(260, 40)))
    {
        m_money -= currentPrice;
        m_autoCoinCount++;
        m_autoCoinPrice *= 1.2f; // Le prix augmente de 20%
        m_autoCoinDelay -= 0.5f; // Le cooldown diminue
    }
    if (!canBuy) ImGui::EndDisabled();

    ImGui::Spacing();
    ImGui::Text("Niveau : %d", m_autoCoinCount);
    ImGui::Text("Intervalle : %.1fs", m_autoCoinDelay);

    if (m_autoCoinDelay <= 0.5f) {
        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "VITESSE MAX !");
    }

    ImGui::End();
}