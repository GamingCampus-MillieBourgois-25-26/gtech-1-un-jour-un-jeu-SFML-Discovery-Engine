#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/BHScenesSyl/BulletHellScene.h"
#include "Scenes/TDScenesSyl/TDScene.h"
#include "Scenes/ClickerScenesSyl/ClickerScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<TDScene>();

    engine->Run();

    return 0;
}
