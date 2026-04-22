#pragma once
#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Engine.h"
#include "Core/GameObject.h"

namespace BulletHell_J {
    class PlayerJ : public Component {
    public:
        int hp = 5;
        float speed = 250.0f;

        // On ne les déclare QU'UNE SEULE FOIS ici
        float invulTimer = 0.0f;
        float cooldownTimer = 0.0f;

        void Update(const float _dt) override {
            if (invulTimer > 0) invulTimer -= _dt;
            if (cooldownTimer > 0) cooldownTimer -= _dt;

            Maths::Vector2f pos = GetOwner()->GetPosition();
            if (InputModule::GetKey(sf::Keyboard::Key::Z)) pos.y -= speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) pos.y += speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) pos.x -= speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::D)) pos.x += speed * _dt;
            GetOwner()->SetPosition(pos);

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Space) && cooldownTimer <= 0) {
                invulTimer = 1.0f;
                cooldownTimer = 3.0f; // 1s de pouvoir + 2s de recharge
            }
        }
    };
}