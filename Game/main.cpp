#include "Engine.h"
#include "SceneModule.h"
#include "MenuScene.h"
#include "SpawnQueue.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();
    engine->Init(_argc, _argv);

    // Flush global — appelé APRÈS Scene::Present(), hors itération
    engine->GetModuleManager()
        ->GetModule<SceneModule>()
        ->onPresent = []() {
        TowerDefence::SpawnQueue::Get().Flush();
        };

    engine->GetModuleManager()
        ->GetModule<SceneModule>()
        ->SetScene<MenuScene>();

    engine->Run();
    return 0;
}