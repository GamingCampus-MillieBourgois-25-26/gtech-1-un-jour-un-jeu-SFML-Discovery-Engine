
#include "PlayerS.h"
#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Modules/AssetsModule.h"
#include "Maths/Vector2.h"
#include "Components/SpriteRenderer.h"
#include "BulletS.h"

/*
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

       /* // Application du mouvement sur le GameObject owner
        Maths::Vector2f currentPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(currentPos + (move * speedS * dt));*/
//    }
    
//}*/
