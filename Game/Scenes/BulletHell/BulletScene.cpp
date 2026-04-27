#include "BulletScene.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "WindowModule.h"
#include "BulletHell/Bullet.h"
#include "BulletHell/Shooter.h"

BulletHell::BulletScene::BulletScene() : Scene("BulletScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    Texture* sr_player = assets_module->LoadAsset<Texture>("fish_red.png");
    GameObject* player = CreateGameObject("Player");
    player->SetRotation(sf::degrees(90));
    player->SetPosition(Maths::Vector2f(300, 300)); 
    player->CreateComponent<SpriteRenderer>(sr_player);
    player->CreateComponent<Shooter>();
}