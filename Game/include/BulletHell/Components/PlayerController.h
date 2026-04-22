#pragma once

#include <vector>
#include <string>

#include "Core/Component.h"
#include "Maths/Vector2.h"

class GameObject;

namespace bulletHell
{
    class PlayerController final : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;
        void OnGUI() override;

        void SetBulletPool(const std::vector<GameObject*>& _bulletPool);
        void SetEnemyBulletPool(const std::vector<GameObject*>& _enemyBulletPool);
        void SetHitboxObject(GameObject* _hitboxObject);
        void SetBossObject(GameObject* _bossObject);

        int GetLives() const;
        bool IsDead() const;
        bool IsFocusMode() const;

    private:
        void HandleMovement(float _delta_time);
        void HandleShoot(float _delta_time);
        void HandleEnemyBulletCollision(float _delta_time);

        void FireBulletFromPool(const Maths::Vector2f& _spawnPosition,
            const Maths::Vector2f& _direction);

        Maths::Vector2f GetFocusedShotDirection() const;
        void ApplyPlayerVisualSize();
        void UpdateHitboxVisual();

        void SaveConfig() const;
        void LoadConfig();

    private:
        float moveSpeed = 280.f;
        float focusMoveSpeed = 120.f;
        float shootCooldown = 0.10f;
        float shootTimer = 0.0f;

        Maths::Vector2f playerSize = { 1.0f, 1.0f };
        Maths::Vector2f bulletSize = { 4.0f, 12.0f };

        float bulletSpeed = 700.0f;

        Maths::Vector2f leftBulletOffset = { -6.0f, -20.0f };
        Maths::Vector2f rightBulletOffset = { 6.0f, -20.0f };

        float hitRadius = 10.0f;
        int lives = 3;

        float invulnerabilityDuration = 1.0f;
        float invulnerabilityTimer = 0.0f;

        bool dead = false;
        bool focusMode = false;

        bool autoTargetInFocus = true;
        float autoTargetStrength = 0.35f;

        GameObject* hitboxObject = nullptr;
        GameObject* bossObject = nullptr;
        float hitboxVisualSize = 6.0f;

        std::vector<GameObject*> bulletPool;
        std::vector<GameObject*> enemyBulletPool;
        int nextBulletIndex = 0;
    };
}