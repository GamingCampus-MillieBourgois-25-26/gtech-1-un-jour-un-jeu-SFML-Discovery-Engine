#include "Asteroid.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "Health.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"

void Asteroid::Update(float dt)
{
    // 1. Déplacement
    auto pos = GetOwner()->GetPosition();
    pos.y += speed * dt;
    GetOwner()->SetPosition(pos);

    // 2. Récupération sécurisée de la scène par son nom
    auto* mm = Engine::GetInstance()->GetModuleManager();
    auto* sceneModule = mm->GetModule<SceneModule>();
    if (!sceneModule) return;

    // On cible spécifiquement la scène de jeu "BulletHell"
    Scene* scene = sceneModule->GetSceneByName("BulletHell");
    if (!scene) return;

    // 3. Collision avec le joueur
    GameObject* player = scene->FindGameObject("Player");
    if (player)
    {
        auto* playerCol = player->GetComponent<SquareCollider>();
        auto* myCol = GetOwner()->GetComponent<SquareCollider>();

        if (playerCol && myCol && SquareCollider::IsColliding(*myCol, *playerCol))
        {
            // ? UTILISE TakeDamage pour respecter l'invulnérabilité
            auto* hp = player->GetComponent<Health>();
            if (hp) hp->TakeDamage(1);

            // Détruire l'astéroïde après l'impact
            GetOwner()->Destroy();
            return; // On sort pour éviter de tester le "hors écran" sur un objet mort
        }
    }

    // 4. Destruction si hors écran (optimisation)
    if (pos.y > 1000.f) // Ajusté à 800 pour être sûr qu'il soit bien sorti
    {
        GetOwner()->Destroy();
    }
}