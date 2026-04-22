#pragma once
#include "Core/Scene.h"
#include "Core/GameObject.h"
// IMPORTANT : Inclure les headers des composants AVANT de les utiliser dans CreateComponent
#include "PlayerJ.h" 
#include "EnemyJ.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"

namespace BulletHell_J {
    class BulletHellSceneJ final : public Scene {
    public:
        BulletHellSceneJ() : Scene("BulletHellJ") {

            // Création du Player
            GameObject* player = CreateGameObject("PlayerJ");
            player->SetPosition({ 100.f, 300.f });

            // Si cette ligne s'affiche en rouge, vérifie le chemin de l'include de PlayerJ.h plus haut
            player->CreateComponent<PlayerJ>();

            SquareCollider* col = player->CreateComponent<SquareCollider>();
            col->SetWidth(20.f);
            col->SetHeight(20.f);

            RectangleShapeRenderer* render = player->CreateComponent<RectangleShapeRenderer>();
            render->SetSize({ 20.f, 20.f });
            render->SetColor(sf::Color::Green);

            // Création de l'Ennemi
            GameObject* enemy = CreateGameObject("EnemyJ");
            enemy->SetPosition({ 300.f, 300.f });
            enemy->CreateComponent<EnemyJ>();

            RectangleShapeRenderer* eRender = enemy->CreateComponent<RectangleShapeRenderer>();
            eRender->SetSize({ 40.f, 40.f });
            eRender->SetColor(sf::Color::Red);
        }
    };
}