#include "ClickerChris/ClickerScene.h"

#include "ClickerChris/ClickerController.h"
#include "ClickerChris/ClickerButton.h"

#include "Engine.h"
#include "ModuleManager.h"
#include "Modules/AssetsModule.h"

#include "Core/GameObject.h"
#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include "Maths/Vector2.h"

ClickerChris::ClickerScene::ClickerScene()
    : Scene("ClickerScene")
{
    AssetsModule* assets = Engine::GetInstance()
        ->GetModuleManager()
        ->GetModule<AssetsModule>();

    Texture* backgroundTexture = assets->LoadAsset<Texture>(
        "ClickerChris/clickerbg.png"
    );

    Texture* buttonTexture = assets->LoadAsset<Texture>(
        "ClickerChris/Tiles/Large tiles/Thick outline/tile_0000.png"
    );

    GameObject* backgroundObj = CreateGameObject("Background");
    backgroundObj->SetPosition(Maths::Vector2f(0.f, 0.f));
    backgroundObj->SetScale(Maths::Vector2f(6.f, 6.f));
    backgroundObj->CreateComponent<SpriteRenderer>(backgroundTexture);

    GameObject* controllerObj = CreateGameObject("ClickerController");
    ClickerController* controller = controllerObj->CreateComponent<ClickerController>();

    GameObject* buttonObj = CreateGameObject("Button");
    buttonObj->SetPosition(Maths::Vector2f(100.f, 100.f));
    buttonObj->SetScale(Maths::Vector2f(4.f, 4.f));
    buttonObj->CreateComponent<SpriteRenderer>(buttonTexture);

    ClickerButton* button = buttonObj->CreateComponent<ClickerButton>();
    button->SetController(controller);
}