#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

namespace bulletHell
{
    class BulletComponent final : public Component
    {
    public:
        void Update(float _delta_time) override;

        void Fire(const Maths::Vector2f& _startPosition,
            const Maths::Vector2f& _direction,
            float _speed);

        void Deactivate();

        bool IsActive() const;

    private:
        bool active = false;
        Maths::Vector2f direction = { 0.f, -1.f };
        float speed = 0.f;
    };
}