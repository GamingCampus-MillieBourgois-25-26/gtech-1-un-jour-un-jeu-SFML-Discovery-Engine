#include "GridManager.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h" 

void GridManager::Start() {
    // Initialiser le vecteur 'grid' ici
}

void GridManager::Update(float _delta_time) {
    if (!isAnimating) {
        HandleInput();
    }
}

CandyType GridManager::GetCandyAt(int x, int y) const {
    // Retourne le type de bonbon à ces coordonnées
    return CandyType::EMPTY;
}

Maths::Vector2f GridManager::GetWorldPosition(int x, int y) const {
    // Calcule la position SFML basée sur GetOwner()->GetPosition()
    return { 0, 0 };
}

void GridManager::HandleInput() {
    // Utiliser InputModule::GetMouseButtonDown
}

void GridManager::Swap(Maths::Vector2i posA, Maths::Vector2i posB) {
    // Logique d'échange
}
