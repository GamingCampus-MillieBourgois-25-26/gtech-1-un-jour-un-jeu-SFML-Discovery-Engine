#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "TDScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<TD::TDScene>();

    engine->Run();

    return 0;
}
