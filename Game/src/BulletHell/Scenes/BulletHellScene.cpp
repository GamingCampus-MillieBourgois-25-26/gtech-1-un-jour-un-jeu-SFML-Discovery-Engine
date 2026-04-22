#include "BulletHell/Scenes/BulletHellScene.h"

#include "Assets/Texture.h"
#include "Modules/AssetsModule.h"

#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h"

#include "BulletHell/Components/PlayerController.h"
#include "BulletHell/Components/BulletComponent.h"
#include "BulletHell/Components/BossComponent.h"
#include "BulletHell/UI/BossHUDComponent.h"
#include "BulletHell/UI/PlayerHUDComponent.h"

namespace bulletHell
{
    BulletHellScene::BulletHellScene()
        : Scene("BulletHellScene")
    {
        CreatePlayer();
        CreatePlayerBulletPool();
        CreateEnemyBulletPool();
        CreateBoss();
        CreateHUD();
    }

    void BulletHellScene::CreatePlayer()
    {
        AssetsModule* assetsModule = Component::GetModule<AssetsModule>();
        if (assetsModule != nullptr)
        {
            playerTexture = assetsModule->LoadAsset<Texture>("BulletHell/Ships/ship_0000.png");
            bulletTexture = assetsModule->LoadAsset<Texture>("BulletHell/Tiles/tile_0000.png");
        }

        player = CreateGameObject("Player");
        player->SetPosition({ 400.f, 500.f });
        player->SetScale({ 1.0f, 1.0f });

        if (playerTexture != nullptr)
        {
            player->CreateComponent<SpriteRenderer>(playerTexture);
        }
        else
        {
            RectangleShapeRenderer* renderer = player->CreateComponent<RectangleShapeRenderer>();
            renderer->SetColor(sf::Color::Green);
            renderer->SetSize({ 20.f, 20.f });
        }

        PlayerController* playerController = player->CreateComponent<PlayerController>();

        GameObject* hitbox = CreateGameObject("PlayerHitbox");
        hitbox->SetPosition(player->GetPosition());
        hitbox->SetScale({ 1.0f, 1.0f });

        RectangleShapeRenderer* hitboxRenderer = hitbox->CreateComponent<RectangleShapeRenderer>();
        hitboxRenderer->SetColor(sf::Color::White);
        hitboxRenderer->SetSize({ 0.0f, 0.0f });

        playerController->SetHitboxObject(hitbox);
    }

    void BulletHellScene::CreatePlayerBulletPool()
    {
        constexpr int bulletCount = 96;

        for (int i = 0; i < bulletCount; ++i)
        {
            GameObject* bullet = CreateGameObject("PlayerBullet");
            bullet->SetPosition({ -10000.0f, -10000.0f });
            bullet->SetScale({ 0.35f, 0.35f });

            if (bulletTexture != nullptr)
            {
                bullet->CreateComponent<SpriteRenderer>(bulletTexture);
            }
            else
            {
                RectangleShapeRenderer* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
                renderer->SetColor(sf::Color::Cyan);
                renderer->SetSize({ 4.0f, 12.0f });
            }

            bullet->CreateComponent<BulletComponent>();
            playerBullets.push_back(bullet);
        }

        if (player != nullptr)
        {
            PlayerController* playerController = player->GetComponent<PlayerController>();
            if (playerController != nullptr)
            {
                playerController->SetBulletPool(playerBullets);
            }
        }
    }

    void BulletHellScene::CreateEnemyBulletPool()
    {
        constexpr int bulletCount = 256;

        for (int i = 0; i < bulletCount; ++i)
        {
            GameObject* bullet = CreateGameObject("EnemyBullet");
            bullet->SetPosition({ -10000.0f, -10000.0f });
            bullet->SetScale({ 0.45f, 0.45f });

            if (bulletTexture != nullptr)
            {
                bullet->CreateComponent<SpriteRenderer>(bulletTexture);
            }
            else
            {
                RectangleShapeRenderer* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
                renderer->SetColor(sf::Color(255, 110, 110));
                renderer->SetSize({ 10.0f, 10.0f });
            }

            bullet->CreateComponent<BulletComponent>();
            enemyBullets.push_back(bullet);
        }

        if (player != nullptr)
        {
            PlayerController* playerController = player->GetComponent<PlayerController>();
            if (playerController != nullptr)
            {
                playerController->SetEnemyBulletPool(enemyBullets);
            }
        }
    }

    void BulletHellScene::CreateBoss()
    {
        AssetsModule* assetsModule = Component::GetModule<AssetsModule>();
        if (assetsModule != nullptr)
        {
            bossTexture = assetsModule->LoadAsset<Texture>("BulletHell/Ships/ship_0006.png");

            if (bulletTexture == nullptr)
            {
                bulletTexture = assetsModule->LoadAsset<Texture>("BulletHell/Tiles/tile_0000.png");
            }
        }

        boss = CreateGameObject("Boss");
        boss->SetPosition({ 400.0f, 120.0f });
        boss->SetScale({ 1.0f, 1.0f });

        if (bossTexture != nullptr)
        {
            boss->CreateComponent<SpriteRenderer>(bossTexture);
        }
        else
        {
            RectangleShapeRenderer* renderer = boss->CreateComponent<RectangleShapeRenderer>();
            renderer->SetColor(sf::Color::Red);
            renderer->SetSize({ 48.0f, 48.0f });
        }

        BossComponent* bossComponent = boss->CreateComponent<BossComponent>();
        bossComponent->SetPlayerBulletPool(playerBullets);
        bossComponent->SetEnemyBulletPool(enemyBullets);

        if (player != nullptr)
        {
            PlayerController* playerController = player->GetComponent<PlayerController>();
            if (playerController != nullptr)
            {
                playerController->SetBossObject(boss);
            }
        }
    }

    void BulletHellScene::CreateHUD()
    {
        GameObject* bossHudObject = CreateGameObject("BossHUD");
        BossHUDComponent* bossHud = bossHudObject->CreateComponent<BossHUDComponent>();

        if (boss != nullptr)
        {
            BossComponent* bossComponent = boss->GetComponent<BossComponent>();
            if (bossComponent != nullptr)
            {
                bossHud->SetBoss(bossComponent);
            }
        }

        GameObject* playerHudObject = CreateGameObject("PlayerHUD");
        PlayerHUDComponent* playerHud = playerHudObject->CreateComponent<PlayerHUDComponent>();

        if (player != nullptr)
        {
            PlayerController* playerController = player->GetComponent<PlayerController>();
            if (playerController != nullptr)
            {
                playerHud->SetPlayer(playerController);
            }
        }
    }
}