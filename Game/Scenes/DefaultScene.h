#pragma once

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "Assets/Texture.h"

// Inclusions de tes scripts
#include "Player.h"
#include "Shooter.h"
#include "Health.h"
#include "GameManager.h"
#include "AsteroidSpawner.h"
#include "SquareCollider.h"

class BulletHellScene final : public Scene
{
public:
    // On garde le constructeur pour définir le nom et l'état initial
    BulletHellScene() : Scene("BulletHell", false)
    {
        // On appelle une fonction d'initialisation pour tout créer
        InitScene();
    }

private:
    void InitScene()
    {
        // 1. GAME MANAGER
        // Essentiel pour gérer les phases de jeu
        GameObject* manager = CreateGameObject("GameManager");
        manager->CreateComponent<GameManager>();

        // 2. SPAWNER D'ASTEROÏDES
        // Si les astéroïdes ne s'affichent pas, vérifie que ce composant 
        // n'attend pas un événement de GameManager
        GameObject* spawner = CreateGameObject("Spawner");
        spawner->CreateComponent<AsteroidSpawner>();

        // 3. PLAYER
        GameObject* player = CreateGameObject("Player");
        player->SetPosition(Maths::Vector2f(400.f, 400.f));
        player->SetScale(Maths::Vector2f(0.7f, 0.7f));

        // Collider
        auto* playerCol = player->CreateComponent<SquareCollider>();
        if (playerCol) {
            playerCol->SetWidth(40.0f);
            playerCol->SetHeight(40.0f);
        }

        // Composants gameplay
        player->CreateComponent<Player>();
        player->CreateComponent<Shooter>();

        // Vie
        auto* hp = player->CreateComponent<Health>();
        if (hp) {
            hp->currentHealth = 10;
        }

        // 4. CHARGEMENT DES ASSETS
        AssetsModule* assets = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<AssetsModule>();

        if (assets) {
            Texture* playerTexture = assets->LoadAsset<Texture>("enemyRed5.png");
            if (playerTexture) {
                player->CreateComponent<SpriteRenderer>(playerTexture);
            }
        }
    }
};