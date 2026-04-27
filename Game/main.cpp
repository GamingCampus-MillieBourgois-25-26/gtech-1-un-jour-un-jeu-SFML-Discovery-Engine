#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "Scenes/Tetris/TetrisScene.h"
#include "Scenes/BulletHell/BulletScene.h"
#include "Scenes/Runner/RunnerScene.h"
#include "iostream"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Runner::RunnerScene>();
    
    
    engine->Run();

    return 0;
}
