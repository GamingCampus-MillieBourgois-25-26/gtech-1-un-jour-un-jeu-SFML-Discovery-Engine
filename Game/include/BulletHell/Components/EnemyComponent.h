#pragma once

#include <vector>

#include "Core/Component.h"
#include "Maths/Vector2.h"

class GameObject;

namespace bulletHell
{
    class EnemyComponent final : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;
        void OnGUI() override;

        void SetBulletPool(const std::vector<GameObject*>& _bulletPool);

    private:
        void HandleMovement(float _delta_time);
        void HandleShoot(float _delta_time);
        void FireBulletFromPool(const Maths::Vector2f& _direction);
        Maths::Vector2f RotateVectorDegrees(const Maths::Vector2f& _vector, float _degrees) const;

        void SaveConfig() const;
        void LoadConfig();

    private:
        Maths::Vector2f targetPosition = { 400.0f, 140.0f };
        float moveSpeed = 120.0f;
        bool reachedTarget = false;

        float shootCooldown = 0.35f;
        float shootTimer = 0.0f;
        float bulletSpeed = 260.0f;

        Maths::Vector2f bulletSize = { 10.0f, 10.0f };
        Maths::Vector2f bulletSpawnOffset = { 0.0f, 24.0f };

        int spreadBulletCount = 5;
        float spreadAngleDegrees = 40.0f;

        std::vector<GameObject*> bulletPool;
        int nextBulletIndex = 0;
    };
}