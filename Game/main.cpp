#include "Engine.h"
#include "Modules/SceneModule.h"

#include "MenuScene.h"
#include "Scenes/DefaultScene.h"
#include "TowerDefenseScene.h"
#include "ClickerScene.h"
#include "SceneModule.h"
#include "MenuScene.h"
#include "SpawnQueue.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();
    engine->Init(_argc, _argv);

    auto* sm = engine->GetModuleManager()->GetModule<SceneModule>();
    // Flush global — appelé APRÈS Scene::Present(), hors itération
    engine->GetModuleManager()
        ->GetModule<SceneModule>()
        ->onPresent = []() {
        TowerDefence::SpawnQueue::Get().Flush();
        };

    sm->CreateScene<MenuScene>();
    sm->CreateScene<BulletHellScene>();
    sm->CreateScene<TowerDefenseScene>();
    sm->CreateScene<ClickerScene>();
    engine->GetModuleManager()
        ->GetModule<SceneModule>()
        ->SetScene<MenuScene>();

    engine->Run();

    return 0;
}
