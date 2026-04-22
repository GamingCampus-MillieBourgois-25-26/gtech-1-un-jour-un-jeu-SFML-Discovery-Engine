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

int RandomInt(const int _min, const int _max)
{
    thread_local std::mt19937_64 gen(static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution dist(static_cast<float>(_min), static_cast<float>(_max));
    return dist(gen);
}

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* sr_player = assets_module->LoadAsset<Texture>("player.png");
    GameObject* const& logo = CreateGameObject("SFML Logo");
    GameObject* player = CreateGameObject("Player");
    player->CreateComponent<RectangleShapeRenderer>();
    player->CreateComponent<Player>();
    player->CreateComponent<SpriteRenderer>(sr_player);
    
}

