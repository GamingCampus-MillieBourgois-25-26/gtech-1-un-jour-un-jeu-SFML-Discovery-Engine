#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
#include "Scenes/Tetris/TetrisScene.h"
#include "Scenes/BulletHell/BulletScene.h"
#include "iostream"
int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<BulletHell::BulletScene>();
    
    engine->GetModuleManager()->GetModule<WindowModule>()->SetSize(Maths::Vector2u(700, 920));
    engine->Run();

    return 0;
}
