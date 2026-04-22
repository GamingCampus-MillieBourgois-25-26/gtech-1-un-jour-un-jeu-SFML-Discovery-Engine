#pragma once
#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h"
#include <iostream>

namespace BulletHell_J {
    class PlayerJ : public Component {
    public:
        int hp = 5;
        float speed = 250.0f;
        float invulTimer = 0.0f;
        float cooldownTimer = 0.0f;

        void Update(const float _dt) override {
            if (invulTimer > 0) invulTimer -= _dt;
            if (cooldownTimer > 0) cooldownTimer -= _dt;

            Maths::Vector2f pos = GetOwner()->GetPosition();

            // Utilisation de sf::Keyboard::Key pour correspondre à ton InputModule
            if (InputModule::GetKey(sf::Keyboard::Key::Z)) pos.y -= speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) pos.y += speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) pos.x -= speed * _dt;
            if (InputModule::GetKey(sf::Keyboard::Key::D)) pos.x += speed * _dt;

            // Mise à jour de la position du GameObject
            GetOwner()->SetPosition(pos);

            // Compétence spéciale (Espace)
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Space) && cooldownTimer <= 0) {
                invulTimer = 1.0f;
                cooldownTimer = 3.0f;
            }
        }

        void TakeDamage() {
            if (invulTimer <= 0) {
                hp--;
                invulTimer = 1.0f;
                std::cout << "Player Hit! HP: " << hp << std::endl;
            }
        }
    };
}