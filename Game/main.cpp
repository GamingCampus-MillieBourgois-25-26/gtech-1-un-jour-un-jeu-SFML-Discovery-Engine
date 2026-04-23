#include "Engine.h"
#include "SceneModule.h"
#include "TowerDefense/TowerLevel.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<TowerDefense::TowerLevel>();

    engine->Run();

    return 0;
}
