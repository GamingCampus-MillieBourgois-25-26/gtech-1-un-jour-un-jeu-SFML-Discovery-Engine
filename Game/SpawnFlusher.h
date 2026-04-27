#pragma once
#include "Core/Component.h"

namespace TowerDefence {
    class SpawnFlusher : public Component
    {
    public:
        void Present() override;
    };
}