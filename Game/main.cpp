#include "Engine.h"
#include "SceneModule.h"
#include "BulletHellChris/Scenes/BulletHellScene.h"
#include "TowerDefenseChris/TowerDefenseScene.h"
#include "ClickerChris/ClickerScene.h"
#include "Scenes/BHScenesSyl/BulletHellScene.h"
#include "Scenes/TDScenesSyl/TDScene.h"
#include "Scenes/ClickerScenesSyl/ClickerScene.h"


int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()
        /*->SetScene<TowerDefense::TowerDefenseScene>();*/
        /*->SetScene<BullethellChris::BulletHell>();*/
        /*->SetScene<BulletHellScene>();*/
        /*->SetScene<TDScene>();*/
        /*->SetScene<ClickerScene>();*/
        ->SetScene<ClickerChris::ClickerScene>();

    engine->Run();

    return 0;
}
