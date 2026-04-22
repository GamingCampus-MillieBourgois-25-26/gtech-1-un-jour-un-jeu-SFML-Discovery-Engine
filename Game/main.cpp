#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Demo::DemoScene>();
    
    engine->GetModuleManager()->GetModule<WindowModule>()->SetSize(Maths::Vector2u(1080, 720));

    engine->Run();

    return 0;
}
