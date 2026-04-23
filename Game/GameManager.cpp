#include "GameManager.h"
#include <iostream>
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"

// Spawners
#include "AsteroidSpawner.h"
#include "BulletHellSpawner.h"

void GameManager::Update(float dt)
{
    timer += dt;

    if (currentPhase == GamePhase::Asteroids1 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::BulletHell1);
    }
    else if (currentPhase == GamePhase::BulletHell1 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::Asteroids2);
    }
    else if (currentPhase == GamePhase::Asteroids2 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::BulletHell2);
    }
}

void GameManager::SwitchPhase(GamePhase newPhase)
{
    currentPhase = newPhase;
    timer = 0.f;

    std::cout << "--- CHANGEMENT DE PHASE : " << (int)newPhase << " ---" << std::endl;

    SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sceneModule) return;

    Scene* scene = sceneModule->GetSceneByName("BulletHell");
    if (!scene) return;

    // 1. NETTOYAGE SÉCURISÉ
    for (const auto& obj : scene->GetGameObjects())
    {
        if (obj->GetName() == "Spawner")
        {
            // On tente de récupérer le script d'astéroïdes pour l'éteindre
            auto* astero = obj->GetComponent<AsteroidSpawner>();
            if (astero) astero->isEnabled = false;

            // On tente de récupérer le script de Bullet Hell pour l'éteindre
            auto* bh = obj->GetComponent<BulletHellSpawner>();
            if (bh) bh->isEnabled = false;

            // On renomme pour éviter les conflits et on détruit
            obj->SetName("OldSpawner");
            obj->Destroy();
        }

        // Nettoyage des astéroïdes restants à l'écran pour la clarté
        if (newPhase == GamePhase::BulletHell1 || newPhase == GamePhase::BulletHell2) {
            if (obj->GetName() == "Asteroid") obj->Destroy();
        }
    }

    // 2. CRÉATION DU NOUVEAU SPAWNER
    GameObject* spawner = scene->CreateGameObject("Spawner");
    if (!spawner) return;

    // --- LOGIQUE ASTÉROÏDES (Phases 1 et 3) ---
    if (newPhase == GamePhase::Asteroids1 || newPhase == GamePhase::Asteroids2)
    {
        auto* script = spawner->CreateComponent<AsteroidSpawner>();
        if (script) {
            script->isEnabled = true; // On s'assure qu'il est bien allumé
            if (newPhase == GamePhase::Asteroids2) {
                script->canSpawnLaser = true;
            }
            else {
                script->canSpawnLaser = false;
            }
        }
    }
    // --- LOGIQUE BULLET HELL (Phases 2 et 4) ---
    else if (newPhase == GamePhase::BulletHell1 || newPhase == GamePhase::BulletHell2)
    {
        auto* script = spawner->CreateComponent<BulletHellSpawner>();
        if (script) {
            script->isEnabled = true; // On s'assure qu'il est bien allumé
            if (newPhase == GamePhase::BulletHell2) {
                script->canSpawnLaser = true;
            }
            else {
                script->canSpawnLaser = false;
            }
        }
    }
}