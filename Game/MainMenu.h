#pragma once
#include "Core/Component.h"
#include "Modules/InputModule.h" // Vérifie le chemin vers InputModule
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include <iostream>

class MainMenu : public Component
{
public:
    void Update(float _dt) override
    {
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (!sm) return;

        // CORRECTION 1 : Utilise KeyDown (ou équivalent) pour éviter de déclencher 
        // le changement 60 fois par seconde si tu restes appuyé.
        if (InputModule::GetKey(sf::Keyboard::Key::A))
        {
            LaunchGame(sm, "BulletHell");
        }

        // CORRECTION 2 : Attention au ";" après le if ! 
        // Ton code original avait un ";" qui lançait le TowerDefense instantanément.
        if (InputModule::GetKey(sf::Keyboard::Key::Z))
        {
            LaunchGame(sm, "TowerDefense");
        }
    }

private:
    void LaunchGame(SceneModule* _sm, const std::string& _gameName)
    {
        Scene* target = _sm->GetSceneByName(_gameName);
        Scene* menu = _sm->GetSceneByName("MenuScene");

        if (target && menu)
        {
            std::cout << "Changement vers : " << _gameName << std::endl;
            target->Enable();
            menu->Disable();
        }
    }
};