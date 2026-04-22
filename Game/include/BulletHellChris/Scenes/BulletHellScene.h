#pragma once

#include <vector>

#include "Core/Scene.h"

class GameObject;
class Texture;

namespace bulletHell
{
    class BulletHellScene final : public Scene
    {
    public:
        BulletHellScene();

    private:
        void CreateBackground();
        void CreatePlayer();
        void CreatePlayerBulletPool();
        void CreateEnemyBulletPool();
        void CreateBoss();
        void CreateHUD();

    private:
        GameObject* player = nullptr;
        GameObject* boss = nullptr;

        std::vector<GameObject*> playerBullets;
        std::vector<GameObject*> enemyBullets;

        Texture* backgroundTexture = nullptr;
        Texture* playerTexture = nullptr;
        Texture* bossTexture = nullptr;
        Texture* bulletTexture = nullptr;
    };
}