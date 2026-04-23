#pragma once

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "MainMenu.h" // On inclut le composant que tu as écrit

class MenuScene final : public Scene
{
public:
    // Le moteur appelle ce constructeur sans arguments
    MenuScene() : Scene("MenuScene", true) // true = active au lancement
    {
        // 1. On crée un GameObject qui servira de support à la logique du menu
        GameObject* menuManager = CreateGameObject("MenuManager");

        // 2. On lui attache ton composant MainMenu (celui qui gère les touches A et Z)
        if (menuManager)
        {
            menuManager->CreateComponent<MainMenu>();
        }

        // --- OPTIONNEL : Ajoute ici des visuels pour ne pas avoir un écran noir ---
        // Exemple : un GameObject avec un SpriteRenderer pour afficher un logo ou un fond
    }
};