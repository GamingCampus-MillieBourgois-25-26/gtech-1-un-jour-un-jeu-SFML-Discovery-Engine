#include "Engine.h"
#include "SceneModule.h"
#include "Clicker/ClickerLevel.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Clicker::ClickerLevel>();

    engine->Run();

    return 0;
}
