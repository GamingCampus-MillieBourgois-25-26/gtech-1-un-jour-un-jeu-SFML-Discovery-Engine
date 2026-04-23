#pragma once
/*
#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Modules/AssetsModule.h"
#include "Maths/Vector2.h"
#include "Components/SpriteRenderer.h"
#include "BulletS.h" // On suppose que la classe BulletS est dans le même dossier

namespace BulletHell {

    class PlayerS : public Component {
    private:
        // Caractéristiques du joueur
        float speedS = 450.0f;
        float fireRateS = 0.12f;
        float fireTimerS = 0.0f;

    public:
        PlayerS() = default;
        virtual ~PlayerS() override = default;

        void Update(float _delta_time) override {
            HandleMovementS(_delta_time);
            HandleShootingS(_delta_time);
        }

    private:
        void HandleMovementS(float dt) {
            Maths::Vector2f move = Maths::Vector2f::Zero;

            // Récupération des inputs via ton InputModule
            if (InputModule::GetKey(sf::Keyboard::Key::Z)) move.y -= 1.0f;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) move.y += 1.0f;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) move.x -= 1.0f;
            if (InputModule::GetKey(sf::Keyboard::Key::D)) move.x += 1.0f;

            if (move.x != 0.0f || move.y != 0.0f) {
                // --- Normalisation manuelle (pour éviter l'avantage de vitesse en diagonale) ---
                float length = std::sqrt(move.x * move.x + move.y * move.y);
                move.x /= length;
                move.y /= length;

                // Application du mouvement sur le GameObject owner
                Maths::Vector2f currentPos = GetOwner()->GetPosition();
                GetOwner()->SetPosition(currentPos + (move * speedS * dt));
            }
        }

        void HandleShootingS(float dt) {
            fireTimerS += dt;

            // Tir avec la barre Espace
            if (InputModule::GetKey(sf::Keyboard::Key::Space) && fireTimerS >= fireRateS) {
                ShootS();
                fireTimerS = 0.0f;
            }
        }

        void ShootS() {
            // 1. Création du GameObject de la balle dans la scène actuelle
            Scene* currentScene = GetOwner()->GetScene();
            if (!currentScene) return;

            GameObject* bulletObj = currentScene->CreateGameObject("BulletS");

            // 2. Positionner la balle au niveau du joueur
            bulletObj->SetPosition(GetOwner()->GetPosition());

            // 3. Ajouter le rendu (on récupère la texture via l'AssetsModule)
            auto* assets = GetModule<AssetsModule>();
            Texture* tex = assets->GetAsset<Texture>("bullet_player.png");

            if (tex) {
                bulletObj->CreateComponent<SpriteRenderer>(tex);
            }

            // 4. Ajouter la logique de déplacement de la balle
            auto* bulletLogic = bulletObj->CreateComponent<BulletS>();
            bulletLogic->direction = { 0.0f, -1.0f }; // Le joueur tire vers le haut
            bulletLogic->speed = 800.0f;
        }
    };
}
*/