#pragma once

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

namespace bulletHell
{
    class BulletComponents final : public Component
    {
    public:
        void Update(float _delta_time) override;

        void Fire(const Maths::Vector2f& _startPosition,
            const Maths::Vector2f& _direction,
            float _speed);

        void Activate(const Maths::Vector2f& _direction,
            float _speed,
            const Maths::Vector2f& _visualSize);

        void Deactivate();

        bool IsActive() const;

    private:
        bool active = false;
        Maths::Vector2f direction = Maths::Vector2f(0.0f, -1.0f);
        float speed = 0.0f;
    };
}