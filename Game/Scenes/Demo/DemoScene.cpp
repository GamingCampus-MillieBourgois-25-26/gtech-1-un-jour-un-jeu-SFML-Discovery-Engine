#include "DemoScene.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include "Demo/Tile.h"
#include "Demo/player.h"
#include "Demo/Mechant.h"


Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    Texture* sr_player = assets_module->LoadAsset<Texture>("player.png");
    GameObject* player = CreateGameObject("Player");
    player->CreateComponent<Player>();
    player->CreateComponent<SpriteRenderer>(sr_player);

}



