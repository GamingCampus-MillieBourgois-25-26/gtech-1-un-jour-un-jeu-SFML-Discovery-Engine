#include "Engine.h"
#include "Modules/SceneModule.h"

// Inclus tes fichiers de scènes
#include "MenuScene.h"
#include "Scenes/DefaultScene.h"
#include "TowerDefenseScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();
    engine->Init(_argc, _argv);

    auto* sm = engine->GetModuleManager()->GetModule<SceneModule>();

    // Création des scènes via template
    sm->CreateScene<MenuScene>();        // S'allume seule (true dans son constructeur)
    sm->CreateScene<BulletHellScene>();  // Reste éteinte (false dans son constructeur)
    sm->CreateScene<TowerDefenseScene>(); // Reste éteinte

    engine->Run();
    return 0;
}