#include "Engine.h"
#include "SceneModule.h"
#include "BulletHellScene.h"

int main(int argc, const char** argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(argc, argv);

    engine->GetModuleManager()
        ->GetModule<SceneModule>()
        ->SetScene<BulletHellScene>();

    engine->Run();

    return 0;
}