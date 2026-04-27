#include "ClickerComponent.h"
#include "Core/GameObject.h"
#include "ARenderedComponent.h" // Pour récupérer la taille de l'objet

//void ClickerComponent::Update(float dt)
//{
//    // On récupère la position de la souris (à adapter selon ton InputManager si tu en as un)
//    sf::Vector2i mousePos = sf::Mouse::getPosition();
//    // Note : Idéalement, utilise window.mapPixelToCoords pour la précision
//
//    bool isInside = false;
//
//    // Récupération du rendu pour connaître la zone cliquable
//    auto* renderer = owner->GetComponent<ARenderedComponent>();
//    if (renderer)
//    {
//        sf::FloatRect bounds(owner->transform.position.x, owner->transform.position.y,
//            renderer->GetSize().x, renderer->GetSize().y);
//
//        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
//        {
//            isInside = true;
//        }
//    }
//
//    // Détection du clic (uniquement à l'appui pour éviter le spam par maintien)
//    bool isButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
//
//    if (isInside && isButtonPressed && !wasMouseButtonPressed)
//    {
//        score += pointsPerClick;
//    }
//
//    wasMouseButtonPressed = isButtonPressed;
//}