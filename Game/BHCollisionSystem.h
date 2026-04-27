#pragma once
#include "Core/Component.h"

namespace BulletHell {

    // Vérifie les collisions entre balles et ennemis/joueur chaque frame
    class BHCollisionSystem : public Component
    {
    public:
        void Update(float dt) override;
    };

}