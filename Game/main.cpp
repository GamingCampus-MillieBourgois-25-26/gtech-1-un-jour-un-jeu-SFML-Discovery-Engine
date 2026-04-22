<<<<<<< Updated upstream
#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Demo/DemoScene.h"
=======
#include "Game.h"
>>>>>>> Stashed changes

int main(int argc, const char** argv)
{
<<<<<<< Updated upstream
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Demo::DemoScene>();

    engine->Run();

=======
    Game game;
    game.Run(argc, argv);
>>>>>>> Stashed changes
    return 0;
}