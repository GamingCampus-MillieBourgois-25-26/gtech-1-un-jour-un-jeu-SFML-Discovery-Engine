#include "GameScene.h"
#include "../GridManager.h"
#include "SpriteRenderer.h"
#include "Modules/AssetsModule.h"
#include "RectangleShapeRenderer.h"


namespace Match3 {
    GameScene::GameScene(const std::string& _name, bool _enabled_at_start)
        : Scene(_name, _enabled_at_start)
    {
        GameObject* gridLogic = CreateGameObject("GridLogic");
        GridManager* manager = gridLogic->CreateComponent<GridManager>();

        CreatePool();
        manager->SetPool(&candyPool);

        GameObject* selector = CreateGameObject("Selector");
        auto rectRenderer = selector->CreateComponent<RectangleShapeRenderer>();

        rectRenderer->SetSize({ 64.f, 64.f });
        rectRenderer->SetColor(sf::Color::Transparent); 

        rectRenderer->SetColor(sf::Color(255, 255, 255, 100));

        selector->Disable();
        manager->SetSelector(selector);
    }

    void GameScene::CreatePool() {
        AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

        for (int i = 1; i < (int)CandyType::COUNT; ++i) {
            CandyType type = static_cast<CandyType>(i);

            Texture* tex = nullptr;

            switch (type) {
            case CandyType::RED:
                tex = assets->LoadAsset<Texture>("Carre.png");
                break;
            case CandyType::BLUE:
                tex = assets->LoadAsset<Texture>("Triangle.png");
                break;
            case CandyType::GREEN:
                tex = assets->LoadAsset<Texture>("Hexagone.png");
                break;
            case CandyType::YELLOW:
                tex = assets->LoadAsset<Texture>("Diamand.png");
                break;
            case CandyType::PURPLE:
                tex = assets->LoadAsset<Texture>("Lozange.png");
                break;
            default:
                break;
            }

            sf::Vector2u size = tex->GetTexture().getSize();

            float scaleX = 64.f / size.x;
            float scaleY = 64.f / size.y;

            for (int j = 0; j < 50; ++j) {
                GameObject* candy = CreateGameObject("Candy_" + std::to_string(i));

                candy->CreateComponent<SpriteRenderer>(tex);

                candy->SetScale({ scaleX, scaleY });

                candy->Disable();
                candyPool[type].push_back(candy);
            }
        }
    }
}