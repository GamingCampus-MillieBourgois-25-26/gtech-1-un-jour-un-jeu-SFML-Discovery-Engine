#include "BulletHellSceneS.h"
#include "PlayerS.h"
#include "BHWaveManager.h"
#include "BHCollisionSystem.h"
#include "BHHUD.h"
#include "BHGameState.h"

namespace BulletHell {

    BulletHellSceneS::BulletHellSceneS() : Scene("BulletHell")
    {
        BHGameState::Get().Reset();

        // Joueur
        GameObject* playerObj = CreateGameObject("Player");
        playerObj->SetPosition({ 500.f, 500.f });
        playerObj->CreateComponent<PlayerS>();

        // WaveManager
        GameObject* waveObj = CreateGameObject("WaveManager");
        waveObj->CreateComponent<BHWaveManager>();

        // Système de collision
        GameObject* collObj = CreateGameObject("CollisionSystem");
        collObj->CreateComponent<BHCollisionSystem>();

        // HUD
        GameObject* hudObj = CreateGameObject("HUD");
        hudObj->CreateComponent<BHHUD>();
    }

}