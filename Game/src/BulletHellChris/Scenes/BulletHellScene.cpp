#include "BulletHellChris/Scenes/BulletHellScene.h"

#include "Assets/Texture.h"
#include "Modules/AssetsModule.h"

#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h"

#include "BulletHellChris/Components/PlayerController.h"
#include "BulletHellChris/Components/BulletComponents.h"
#include "BulletHellChris/Components/BossComponent.h"
#include "BulletHellChris/UI/BossHUDComponent.h"
#include "BulletHellChris/UI/PlayerHUDComponent.h"

namespace bulletHell
{
    BulletHellScene::BulletHellScene()
        : Scene("BulletHellScene")
    {
        AssetsModule* assetsModule = Component::GetModule<AssetsModule>();
        if (assetsModule != nullptr)
        {
            backgroundTexture = assetsModule->LoadAsset<Texture>("BulletHellChris/background.jpg");
        }

        CreateBackground();
        CreatePlayer();
        CreatePlayerBulletPool();
        CreateEnemyBulletPool();
        CreateBoss();
        CreateHUD();
    }

    void BulletHellScene::CreateBackground()
    {   
        GameObject* background = CreateGameObject("Background");
        background->SetPosition(Maths::Vector2f(400.0f, 300.0f));
        background->SetScale(Maths::Vector2f(2.0f, 2.0f));

        if (backgroundTexture != nullptr)
        {
            background->CreateComponent<SpriteRenderer>(backgroundTexture);
        }
        else
        {
            RectangleShapeRenderer* renderer = background->CreateComponent<RectangleShapeRenderer>();
            renderer->SetColor(sf::Color(20, 20, 30));
            renderer->SetSize(Maths::Vector2f(800.0f, 600.0f));
        }
    }

    void BulletHellScene::CreatePlayer()
    {
        AssetsModule* assetsModule = Component::GetModule<AssetsModule>();
        if (assetsModule != nullptr)
        {
            playerTexture = assetsModule->LoadAsset<Texture>("BulletHellChris/Ships/ship_0000.png");
            bulletTexture = assetsModule->LoadAsset<Texture>("BulletHellChris/Tiles/tile_0000.png");
        }

        player = CreateGameObject("Player");
        player->SetPosition(Maths::Vector2f(400.f, 500.f));
        player->SetScale(Maths::Vector2f(1.0f, 1.0f));

        if (playerTexture != nullptr)
        {
            player->CreateComponent<SpriteRenderer>(playerTexture);
        }
        else
        {
            RectangleShapeRenderer* renderer = player->CreateComponent<RectangleShapeRenderer>();
            renderer->SetColor(sf::Color::Green);
            renderer->SetSize(Maths::Vector2f(20.f, 20.f));
        }

        PlayerController* playerController = player->CreateComponent<PlayerController>();

        GameObject* hitbox = CreateGameObject("PlayerHitbox");
        hitbox->SetPosition(player->GetPosition());
        hitbox->SetScale(Maths::Vector2f(1.0f, 1.0f));

        RectangleShapeRenderer* hitboxRenderer = hitbox->CreateComponent<RectangleShapeRenderer>();
        hitboxRenderer->SetColor(sf::Color::White);
        hitboxRenderer->SetSize(Maths::Vector2f(0.0f, 0.0f));

        playerController->SetHitboxObject(hitbox);
    }

    void BulletHellScene::CreatePlayerBulletPool()
    {
        constexpr int bulletCount = 96;

        for (int i = 0; i < bulletCount; ++i)
        {
            GameObject* bullet = CreateGameObject("PlayerBullet");
            bullet->SetPosition(Maths::Vector2f(-10000.0f, -10000.0f));
            bullet->SetScale(Maths::Vector2f(0.35f, 0.35f));

            if (bulletTexture != nullptr)
            {
                bullet->CreateComponent<SpriteRenderer>(bulletTexture);
            }
            else
            {
                RectangleShapeRenderer* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
                renderer->SetColor(sf::Color::Cyan);
                renderer->SetSize(Maths::Vector2f(4.0f, 12.0f));
            }

            bullet->CreateComponent<BulletComponents>();
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
            bullet->SetPosition(Maths::Vector2f(-10000.0f, -10000.0f));
            bullet->SetScale(Maths::Vector2f(0.45f, 0.45f));

            if (bulletTexture != nullptr)
            {
                bullet->CreateComponent<SpriteRenderer>(bulletTexture);
            }
            else
            {
                RectangleShapeRenderer* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
                renderer->SetColor(sf::Color(255, 110, 110));
                renderer->SetSize(Maths::Vector2f(10.0f, 10.0f));
            }

            bullet->CreateComponent<BulletComponents>();
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
            bossTexture = assetsModule->LoadAsset<Texture>("BulletHellChris/Ships/ship_0006.png");

            if (bulletTexture == nullptr)
            {
                bulletTexture = assetsModule->LoadAsset<Texture>("BulletHellChris/Tiles/tile_0000.png");
            }
        }

        boss = CreateGameObject("Boss");
        boss->SetPosition(Maths::Vector2f(400.0f, 120.0f));
        boss->SetScale(Maths::Vector2f(1.0f, 1.0f));

        if (bossTexture != nullptr)
        {
            boss->CreateComponent<SpriteRenderer>(bossTexture);
        }
        else
        {
            RectangleShapeRenderer* renderer = boss->CreateComponent<RectangleShapeRenderer>();
            renderer->SetColor(sf::Color::Red);
            renderer->SetSize(Maths::Vector2f(48.0f, 48.0f));
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

        GameObject* bossBarBackground = CreateGameObject("BossBarBackground");
        bossBarBackground->SetPosition(Maths::Vector2f(190.0f, 24.0f));
        bossBarBackground->SetScale(Maths::Vector2f(1.0f, 1.0f));
        RectangleShapeRenderer* bossBarBackgroundRenderer = bossBarBackground->CreateComponent<RectangleShapeRenderer>();
        bossBarBackgroundRenderer->SetColor(sf::Color(40, 40, 40));
        bossBarBackgroundRenderer->SetSize(Maths::Vector2f(420.0f, 20.0f));

        GameObject* bossBarFill = CreateGameObject("BossBarFill");
        bossBarFill->SetPosition(Maths::Vector2f(190.0f, 24.0f));
        bossBarFill->SetScale(Maths::Vector2f(1.0f, 1.0f));
        RectangleShapeRenderer* bossBarFillRenderer = bossBarFill->CreateComponent<RectangleShapeRenderer>();
        bossBarFillRenderer->SetColor(sf::Color(80, 255, 120));
        bossBarFillRenderer->SetSize(Maths::Vector2f(420.0f, 20.0f));

        bossHud->SetBarBackground(bossBarBackground);
        bossHud->SetBarFill(bossBarFill);

        GameObject* playerHudObject = CreateGameObject("PlayerHUD");
        PlayerHUDComponent* playerHud = playerHudObject->CreateComponent<PlayerHUDComponent>();

        if (player != nullptr)
        {
            PlayerController* playerController = player->GetComponent<PlayerController>();
            if (playerController != nullptr)
            {
                playerHud->SetPlayer(playerController);

                const int maxDisplayLives = 10;
                const int startingLives = playerController->GetLives();

                const int pipCount = (startingLives < maxDisplayLives) ? startingLives : maxDisplayLives;
                const float startX = 5.0f;
                const float startY = 5.0f;
                const float pipWidth = 5.0f;
                const float pipHeight = 5.0f;
                const float spacing = 2.0f;

                for (int i = 0; i < pipCount; ++i)
                {
                    GameObject* pip = CreateGameObject("PlayerLifePip");
                    pip->SetPosition(Maths::Vector2f(startX + i * (pipWidth + spacing), startY));
                    pip->SetScale(Maths::Vector2f(1.0f, 1.0f));

                    RectangleShapeRenderer* pipRenderer = pip->CreateComponent<RectangleShapeRenderer>();
                    pipRenderer->SetColor(sf::Color(80, 255, 120));
                    pipRenderer->SetSize(Maths::Vector2f(pipWidth, pipHeight));

                    playerHud->AddLifePip(pip);
                }
            }
        }
    }
}