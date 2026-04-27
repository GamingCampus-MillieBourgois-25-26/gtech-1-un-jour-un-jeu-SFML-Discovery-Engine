#pragma once

#include "Core/Scene.h"
#include "../GridManager.h"
namespace Match3
{
    class GameScene : public Scene
    {
    public:
        explicit GameScene(const std::string& _name, bool _enabled_at_start)
            : Scene(_name, _enabled_at_start)
        {
            GameObject* gridObj = CreateGameObject("GridLogic");
            gridObj->CreateComponent<GridManager>();
        }
        ~GameScene() override = default;
    };
    
}