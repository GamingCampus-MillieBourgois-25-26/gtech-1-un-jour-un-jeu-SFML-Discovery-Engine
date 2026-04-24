#pragma once

#include <vector>

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

namespace bulletHell
{
    struct BossPhaseSettings
    {
        Maths::Vector2f bossScale = Maths::Vector2f(1.0f, 1.0f);

        Maths::Vector2f moveAmplitude = Maths::Vector2f(120.0f, 0.0f);
        Maths::Vector2f moveFrequency = Maths::Vector2f(1.0f, 0.0f);

        float shootCooldown = 0.45f;
        float bulletSpeed = 180.0f;
        Maths::Vector2f bulletSize = Maths::Vector2f(10.0f, 10.0f);
        Maths::Vector2f bulletSpawnOffset = Maths::Vector2f(0.0f, 28.0f);

        int spreadBulletCount = 5;
        float spreadAngleDegrees = 40.0f;

        bool straightBurstEnabled = false;
        float straightBurstSpeed = 280.0f;
        int straightBurstEvery = 2;
    };

    class BossComponent final : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;
        void OnGUI() override;

        void SetPlayerBulletPool(const std::vector<GameObject*>& _bulletPool);
        void SetEnemyBulletPool(const std::vector<GameObject*>& _bulletPool);

        float GetCurrentHealth() const;
        float GetMaxHealth() const;
        int GetPhase() const;
        bool IsDefeated() const;

    private:
        void UpdatePhase();
        void HandleMovement(float _delta_time);
        void HandleShoot(float _delta_time);
        void HandlePlayerBulletCollision();

        void FireBulletFromPool(const Maths::Vector2f& _direction,
            float _speed,
            const Maths::Vector2f& _bulletSize,
            const Maths::Vector2f& _spawnOffset);

        void FireSpread(const BossPhaseSettings& _settings);
        void FireStraightBurst(float _speed,
            const Maths::Vector2f& _bulletSize,
            const Maths::Vector2f& _spawnOffset);

        Maths::Vector2f RotateVectorDegrees(const Maths::Vector2f& _vector, float _degrees) const;

        BossPhaseSettings& GetCurrentPhaseSettings();
        const BossPhaseSettings& GetCurrentPhaseSettings() const;

        void DrawPhaseSettingsGUI(const char* _label, BossPhaseSettings& _settings, bool& _changed);

        void SaveConfig() const;
        void LoadConfig();

    private:
        float maxHealth = 300.0f;
        float currentHealth = 300.0f;

        int phase = 1;
        bool defeated = false;

        float hitRadius = 80.0f;
        Maths::Vector2f hitboxOffset = Maths::Vector2f(0.0f, 0.0f);

        float contactDamage = 1.0f;

        float movementTimer = 0.0f;
        float shootTimer = 0.0f;
        int phaseBurstCounter = 0;

        Maths::Vector2f basePosition = Maths::Vector2f(400.0f, 120.0f);

        BossPhaseSettings phase1Settings;
        BossPhaseSettings phase2Settings;
        BossPhaseSettings phase3Settings;

        std::vector<GameObject*> playerBullets;
        std::vector<GameObject*> enemyBullets;
        int nextEnemyBulletIndex = 0;
    };
}