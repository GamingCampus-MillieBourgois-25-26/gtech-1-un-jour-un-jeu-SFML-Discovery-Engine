#pragma once

#include "Core/Scene.h"
#include <vector>
#include "Maths/Vector2.h"

namespace TD
{
    class TDScene final : public Scene
    {
    public:
        TDScene();

    private:
        void CreateMap();
        void CreatePath();

        std::vector<Maths::Vector2f> pathPoints;
    };
}