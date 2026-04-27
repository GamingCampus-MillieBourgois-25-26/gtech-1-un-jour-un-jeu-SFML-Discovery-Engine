#pragma once

#include "Core/Scene.h"

namespace Demo
{
    class DemoScene final : public Scene
    {
    public:
        DemoScene();

        

        float minSize = 100.f;
        float maxSize = 300.f;
    };
}

