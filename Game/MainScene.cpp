#include "MainScene.h"
#include "ClickArea.h"
#include "ShopPanel.h"
#include <iostream>

void MainScene::Start() const
{
    std::cout << "MainScene Start\n";

    // 🎯 Zone de clic
    GameObject* clickGO = CreateGameObject("ClickArea");
    clickGO->CreateComponent<ClickArea>();

    // 🎯 Shop
    GameObject* shopGO = CreateGameObject("ShopPanel");
    shopGO->CreateComponent<ShopPanel>();
}

void MainScene::Update(float deltaTime) const
{
    // Pour l’instant vide
}