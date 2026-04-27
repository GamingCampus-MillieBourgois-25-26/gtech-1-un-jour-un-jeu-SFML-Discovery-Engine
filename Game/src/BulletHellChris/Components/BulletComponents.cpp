#include "BulletHellChris/Components/BulletComponents.h"

#include "Components/RectangleShapeRenderer.h"

namespace bulletHell
{
    void BulletComponents::Update(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        if (!active)
        {
            return;
        }

        Maths::Vector2f position = owner->GetPosition();
        position += direction * speed * _delta_time;
        owner->SetPosition(position);

        const bool isOutOfBounds =
            position.y < -60.0f ||
            position.y > 760.0f ||
            position.x < -60.0f ||
            position.x > 1360.0f;

        if (isOutOfBounds)
        {
            Deactivate();
        }
    }

    void BulletComponents::Fire(const Maths::Vector2f& _startPosition,
        const Maths::Vector2f& _direction,
        float _speed)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        active = true;
        direction = _direction;
        speed = _speed;
        owner->SetPosition(_startPosition);
    }

    void BulletComponents::Activate(const Maths::Vector2f& _direction,
        float _speed,
        const Maths::Vector2f& _visualSize)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        active = true;
        direction = _direction;
        speed = _speed;

        RectangleShapeRenderer* renderer = owner->GetComponent<RectangleShapeRenderer>();
        if (renderer != nullptr)
        {
            renderer->SetSize(_visualSize);
        }
    }

    void BulletComponents::Deactivate()
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        active = false;
        speed = 0.0f;
        owner->SetPosition({ -10000.0f, -10000.0f });
    }

    bool BulletComponents::IsActive() const
    {
        return active;
    }
}