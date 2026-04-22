#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"
#include "Scenes/buller_hell_F.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<FBHene>();

    engine->Run();

    return 0;
}
