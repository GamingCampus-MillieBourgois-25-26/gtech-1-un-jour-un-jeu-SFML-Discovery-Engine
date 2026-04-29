#include "Match3/Match3Scene.h"
#include "Match3/Match3Controller.h"

#include "Core/GameObject.h"

namespace Match3
{
    Match3Scene::Match3Scene()
        : Scene("Match3Scene")
    {
        GameObject* controller = CreateGameObject("Match3Controller");
        controller->CreateComponent<Match3Controller>();
    }
}