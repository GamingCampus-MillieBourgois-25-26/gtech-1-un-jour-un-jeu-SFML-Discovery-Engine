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
    // 🔹 Récupération du module d’assets
    AssetsModule* assets = Engine::GetInstance()
        ->GetModuleManager()
        ->GetModule<AssetsModule>();

    // 🔹 Chargement du sprite du bouton
    Texture* buttonTexture = assets->LoadAsset<Texture>(
        "ClickerChris/Tiles/Large tiles/Thick outline/tile_0000.png"
    );

    // 🔹 Controller
    GameObject* controllerObj = CreateGameObject("ClickerController");
    ClickerController* controller = controllerObj->CreateComponent<ClickerController>();

    // 🔹 Bouton
    GameObject* buttonObj = CreateGameObject("Button");
    buttonObj->SetPosition(Maths::Vector2f(100.f, 100.f));
    buttonObj->SetScale(Maths::Vector2f(4.f, 4.f));

    // Sprite
    buttonObj->CreateComponent<SpriteRenderer>(buttonTexture);

    // Logique clic
    ClickerButton* button = buttonObj->CreateComponent<ClickerButton>();
    button->SetController(controller);
}