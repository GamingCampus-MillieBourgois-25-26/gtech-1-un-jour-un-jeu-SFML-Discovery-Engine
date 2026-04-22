#pragma once
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "PlayerJ.h"
#include "EnemyJ.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"

namespace BulletHell_J {
    class BulletHellSceneJ final : public Scene {
    public:
        BulletHellSceneJ() : Scene("BulletHellJ") {
            // Player
            GameObject* p = CreateGameObject("PlayerJ");
            p->SetPosition({ 100.f, 300.f });
            p->AddComponent(new PlayerJ());

            SquareCollider* pCol = new SquareCollider();
            pCol->SetWidth(20.f); pCol->SetHeight(20.f);
            p->AddComponent(pCol);

            RectangleShapeRenderer* pR = new RectangleShapeRenderer();
            pR->SetSize({ 20.f, 20.f }); pR->SetColor(sf::Color::Green);
            p->AddComponent(pR);

            // Enemy
            GameObject* e = CreateGameObject("EnemyJ");
            e->SetPosition({ 400.f, 300.f });

            EnemyJ* enemyComp = new EnemyJ();
            enemyComp->sceneRef = this;
            enemyComp->playerRef = p;
            e->AddComponent(enemyComp);

            RectangleShapeRenderer* eR = new RectangleShapeRenderer();
            eR->SetSize({ 40.f, 40.f }); eR->SetColor(sf::Color::Red);
            e->AddComponent(eR);
        }
    };
}