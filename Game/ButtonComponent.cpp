#include "ButtonComponent.h"
#include "Engine.h"
#include "SceneModule.h"
#include "ModuleManager.h"
#include "TowerDefenseScene.h"
#include "BulletHellSceneS.h"
#include "InputModule.h"

void ButtonComponent::Update(float dt)
{
    Maths::Vector2i mouse = InputModule::GetMousePosition();

    sf::Vector2f pos = static_cast<sf::Vector2f>(GetOwner()->GetPosition());
    sf::Vector2f size = static_cast<sf::Vector2f>(GetOwner()->GetScale());

    bounds = sf::FloatRect(pos, size);

    if (InputModule::GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        if (bounds.contains(sf::Vector2f(mouse.x, mouse.y)))
            OnClick();
    }
}

void ButtonComponent::OnClick()
{
    auto* sceneModule = Engine::GetInstance()
        ->GetModuleManager()
        ->GetModule<SceneModule>();

    if (target == ButtonTarget::BulletHell)
        sceneModule->SetScene<BulletHell::BulletHellSceneS>();
    else
        sceneModule->SetScene<TowerDefence::TowerDefenseScene>();
}