#pragma once

#include "Core/Component.h"
#include <SFML/System/Vector2.hpp>

class SpriteRenderer;
class GameObject;

class ClickerLogic final : public Component
{
public:
    void Update(float _dt) override;
    void OnGUI() override;

    int GetMoney() const { return m_money; }

private:
    int m_money = 0;
    int m_gems = 0;
    bool can_Click = true;

    // --- SYSTEME D'UPGRADE ---
    int m_autoCoinCount = 0;
    float m_autoCoinTimer = 0.0f;
    float m_autoCoinDelay = 5.0f;   // N'est plus 'const' car il va diminuer
    float m_autoCoinPrice = 50.0f;  // Le prix devient flottant pour la précision du calcul

    // --- VISUEL FEEDBACK ---
    GameObject* m_feedbackIcon = nullptr;
    SpriteRenderer* m_iconRenderer = nullptr; // Pour un accès direct
    float m_iconDisplayTimer = 0.0f;
};