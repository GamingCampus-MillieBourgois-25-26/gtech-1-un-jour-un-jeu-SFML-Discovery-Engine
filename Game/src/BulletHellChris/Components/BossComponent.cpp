#include "BulletHellChris/Components/BossComponent.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>

#include "imgui.h"

#include "BulletHellChris/BulletHellDebug.h"
#include "BulletHellChris/Components/BulletComponent.h"

namespace bulletHell
{
    void BossComponent::Start()
    {
        phase1Settings.bossScale = Maths::Vector2f(5.0f, 5.0f);
        phase1Settings.moveAmplitude = Maths::Vector2f(120.0f, 50.0f);
        phase1Settings.moveFrequency = Maths::Vector2f(1.0f, 2.0f);
        phase1Settings.shootCooldown = 1.0f;
        phase1Settings.bulletSpeed = 180.0f;
        phase1Settings.bulletSize = Maths::Vector2f(20.0f, 20.0f);
        phase1Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 70.0f);
        phase1Settings.spreadBulletCount = 5;
        phase1Settings.spreadAngleDegrees = 40.0f;
        phase1Settings.straightBurstEnabled = false;
        phase1Settings.straightBurstSpeed = 280.0f;
        phase1Settings.straightBurstEvery = 2;

        phase2Settings.bossScale = Maths::Vector2f(5.0f, 5.0f);
        phase2Settings.moveAmplitude = Maths::Vector2f(180.0f, 50.0f);
        phase2Settings.moveFrequency = Maths::Vector2f(2.0f, 4.0f);
        phase2Settings.shootCooldown = 0.5f;
        phase2Settings.bulletSpeed = 220.0f;
        phase2Settings.bulletSize = Maths::Vector2f(10.0f, 10.0f);
        phase2Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 70.0f);
        phase2Settings.spreadBulletCount = 10;
        phase2Settings.spreadAngleDegrees = 100.0f;
        phase2Settings.straightBurstEnabled = false;
        phase2Settings.straightBurstSpeed = 300.0f;
        phase2Settings.straightBurstEvery = 2;

        phase3Settings.bossScale = Maths::Vector2f(5.0f, 5.0f);
        phase3Settings.moveAmplitude = Maths::Vector2f(180.0f, 60.0f);
        phase3Settings.moveFrequency = Maths::Vector2f(4.0f, 8.0f);
        phase3Settings.shootCooldown = 0.2f;
        phase3Settings.bulletSpeed = 260.0f;
        phase3Settings.bulletSize = Maths::Vector2f(10.0f, 10.0f);
        phase3Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 70.0f);
        phase3Settings.spreadBulletCount = 20;
        phase3Settings.spreadAngleDegrees = 360.0f;
        phase3Settings.straightBurstEnabled = true;
        phase3Settings.straightBurstSpeed = 320.0f;
        phase3Settings.straightBurstEvery = 2;

        LoadConfig();

        currentHealth = maxHealth;
        phase = 1;
        defeated = false;
        movementTimer = 0.0f;
        shootTimer = 0.0f;
        phaseBurstCounter = 0;
    }

    void BossComponent::Update(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        if (defeated)
        {
            return;
        }

        movementTimer += _delta_time;

        UpdatePhase();
        HandleMovement(_delta_time);
        HandleShoot(_delta_time);
        HandlePlayerBulletCollision();

        owner->SetScale(GetCurrentPhaseSettings().bossScale);
    }

    void BossComponent::OnGUI()
    {
        if (!g_showDebugUI)
        {
            return;
        }

        if (!ImGui::Begin("Boss Debug"))
        {
            ImGui::End();
            return;
        }

        bool changed = false;

        ImGui::Text("Boss");
        ImGui::Text("Phase: %d", phase);
        ImGui::Text("HP: %.1f / %.1f", currentHealth, maxHealth);

        changed |= ImGui::DragFloat("Max Health", &maxHealth, 1.0f, 10.0f, 5000.0f);
        changed |= ImGui::DragFloat("Hit Radius", &hitRadius, 0.1f, 2.0f, 200.0f);
        changed |= ImGui::DragFloat2("Hitbox Offset", &hitboxOffset.x, 0.1f, -200.0f, 200.0f);
        changed |= ImGui::DragFloat("Bullet Damage", &contactDamage, 0.1f, 0.1f, 50.0f);
        changed |= ImGui::DragFloat2("Base Position", &basePosition.x, 1.0f, 0.0f, 1200.0f);

        ImGui::Separator();
        DrawPhaseSettingsGUI("Phase 1", phase1Settings, changed);
        ImGui::Separator();
        DrawPhaseSettingsGUI("Phase 2", phase2Settings, changed);
        ImGui::Separator();
        DrawPhaseSettingsGUI("Phase 3", phase3Settings, changed);

        if (ImGui::Button("Reset Boss"))
        {
            currentHealth = maxHealth;
            phase = 1;
            defeated = false;
            movementTimer = 0.0f;
            shootTimer = 0.0f;
            phaseBurstCounter = 0;
        }

        ImGui::SameLine();

        if (ImGui::Button("Save Boss Config"))
        {
            SaveConfig();
        }

        if (changed)
        {
            SaveConfig();
        }

        ImGui::End();
    }

    void BossComponent::SetPlayerBulletPool(const std::vector<GameObject*>& _bulletPool)
    {
        playerBullets = _bulletPool;
    }

    void BossComponent::SetEnemyBulletPool(const std::vector<GameObject*>& _bulletPool)
    {
        enemyBullets = _bulletPool;
        nextEnemyBulletIndex = 0;
    }

    float BossComponent::GetCurrentHealth() const
    {
        return currentHealth;
    }

    float BossComponent::GetMaxHealth() const
    {
        return maxHealth;
    }

    int BossComponent::GetPhase() const
    {
        return phase;
    }

    bool BossComponent::IsDefeated() const
    {
        return defeated;
    }

    void BossComponent::UpdatePhase()
    {
        const float phase2Threshold = maxHealth * 0.66f;
        const float phase3Threshold = maxHealth * 0.33f;

        if (currentHealth > phase2Threshold)
        {
            phase = 1;
        }
        else if (currentHealth > phase3Threshold)
        {
            phase = 2;
        }
        else
        {
            phase = 3;
        }
    }

    void BossComponent::HandleMovement(float _delta_time)
    {
        (void)_delta_time;

        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        const BossPhaseSettings& settings = GetCurrentPhaseSettings();

        const float offsetX = std::sin(movementTimer * settings.moveFrequency.x) * settings.moveAmplitude.x;
        const float offsetY = std::sin(movementTimer * settings.moveFrequency.y) * settings.moveAmplitude.y;

        owner->SetPosition(basePosition + Maths::Vector2f(offsetX, offsetY));
    }

    void BossComponent::HandleShoot(float _delta_time)
    {
        if (enemyBullets.empty())
        {
            return;
        }

        if (shootTimer > 0.0f)
        {
            shootTimer -= _delta_time;
        }

        if (shootTimer > 0.0f)
        {
            return;
        }

        BossPhaseSettings& settings = GetCurrentPhaseSettings();

        FireSpread(settings);
        ++phaseBurstCounter;

        if (settings.straightBurstEnabled &&
            settings.straightBurstEvery > 0 &&
            (phaseBurstCounter % settings.straightBurstEvery) == 0)
        {
            FireStraightBurst(settings.straightBurstSpeed, settings.bulletSize, settings.bulletSpawnOffset);
        }

        shootTimer = settings.shootCooldown;
    }

    void BossComponent::HandlePlayerBulletCollision()
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr || defeated)
        {
            return;
        }

        const Maths::Vector2f bossPosition = owner->GetPosition() + hitboxOffset;
        const float hitRadiusSquared = hitRadius * hitRadius;

        for (GameObject* bulletObject : playerBullets)
        {
            if (bulletObject == nullptr)
            {
                continue;
            }

            BulletComponent* bulletComponent = bulletObject->GetComponent<BulletComponent>();
            if (bulletComponent == nullptr || !bulletComponent->IsActive())
            {
                continue;
            }

            const Maths::Vector2f delta = bulletObject->GetPosition() - bossPosition;
            if (delta.MagnitudeSquared() <= hitRadiusSquared)
            {
                bulletComponent->Deactivate();

                currentHealth -= contactDamage;
                if (currentHealth <= 0.0f)
                {
                    currentHealth = 0.0f;
                    defeated = true;
                }
            }
        }
    }

    void BossComponent::FireBulletFromPool(const Maths::Vector2f& _direction,
        float _speed,
        const Maths::Vector2f& _bulletSize,
        const Maths::Vector2f& _spawnOffset)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr || enemyBullets.empty())
        {
            return;
        }

        const std::size_t poolSize = enemyBullets.size();
        for (std::size_t i = 0; i < poolSize; ++i)
        {
            GameObject* bulletObject = enemyBullets[nextEnemyBulletIndex];
            nextEnemyBulletIndex = (nextEnemyBulletIndex + 1) % static_cast<int>(poolSize);

            if (bulletObject == nullptr)
            {
                continue;
            }

            BulletComponent* bulletComponent = bulletObject->GetComponent<BulletComponent>();
            if (bulletComponent == nullptr || bulletComponent->IsActive())
            {
                continue;
            }

            bulletObject->SetPosition(owner->GetPosition() + _spawnOffset);
            bulletComponent->Activate(_direction, _speed, _bulletSize);
            return;
        }
    }

    void BossComponent::FireSpread(const BossPhaseSettings& _settings)
    {
        if (_settings.spreadBulletCount <= 1)
        {
            FireBulletFromPool(Maths::Vector2f(0.0f, 1.0f), _settings.bulletSpeed, _settings.bulletSize, _settings.bulletSpawnOffset);
            return;
        }

        const float startAngle = -_settings.spreadAngleDegrees * 0.5f;
        const float stepAngle = _settings.spreadAngleDegrees / static_cast<float>(_settings.spreadBulletCount - 1);

        for (int i = 0; i < _settings.spreadBulletCount; ++i)
        {
            const float angle = startAngle + stepAngle * static_cast<float>(i);
            const Maths::Vector2f direction = RotateVectorDegrees(Maths::Vector2f(0.0f, 1.0f), angle);
            FireBulletFromPool(direction, _settings.bulletSpeed, _settings.bulletSize, _settings.bulletSpawnOffset);
        }
    }

    void BossComponent::FireStraightBurst(float _speed,
        const Maths::Vector2f& _bulletSize,
        const Maths::Vector2f& _spawnOffset)
    {
        FireBulletFromPool(Maths::Vector2f(0.0f, 1.0f), _speed, _bulletSize, _spawnOffset);

        Maths::Vector2f leftDir(-0.15f, 1.0f);
        leftDir = leftDir.Normalize();
        FireBulletFromPool(leftDir, _speed, _bulletSize, _spawnOffset);

        Maths::Vector2f rightDir(0.15f, 1.0f);
        rightDir = rightDir.Normalize();
        FireBulletFromPool(rightDir, _speed, _bulletSize, _spawnOffset);
    }

    Maths::Vector2f BossComponent::RotateVectorDegrees(const Maths::Vector2f& _vector, float _degrees) const
    {
        const float radians = _degrees * 3.14159265f / 180.0f;
        const float cosAngle = std::cos(radians);
        const float sinAngle = std::sin(radians);

        return Maths::Vector2f(
            _vector.x * cosAngle - _vector.y * sinAngle,
            _vector.x * sinAngle + _vector.y * cosAngle
        );
    }

    BossPhaseSettings& BossComponent::GetCurrentPhaseSettings()
    {
        switch (phase)
        {
        case 1:  return phase1Settings;
        case 2:  return phase2Settings;
        default: return phase3Settings;
        }
    }

    const BossPhaseSettings& BossComponent::GetCurrentPhaseSettings() const
    {
        switch (phase)
        {
        case 1:  return phase1Settings;
        case 2:  return phase2Settings;
        default: return phase3Settings;
        }
    }

    void BossComponent::DrawPhaseSettingsGUI(const char* _label, BossPhaseSettings& _settings, bool& _changed)
    {
        if (!ImGui::CollapsingHeader(_label, ImGuiTreeNodeFlags_DefaultOpen))
        {
            return;
        }

        std::string prefix = std::string(_label) + " ";

        _changed |= ImGui::DragFloat2((prefix + "Boss Scale").c_str(), &_settings.bossScale.x, 0.01f, 0.1f, 5.0f);
        _changed |= ImGui::DragFloat2((prefix + "Move Amplitude").c_str(), &_settings.moveAmplitude.x, 1.0f, 0.0f, 400.0f);
        _changed |= ImGui::DragFloat2((prefix + "Move Frequency").c_str(), &_settings.moveFrequency.x, 0.01f, 0.0f, 10.0f);

        _changed |= ImGui::DragFloat((prefix + "Shoot Cooldown").c_str(), &_settings.shootCooldown, 0.01f, 0.02f, 5.0f);
        _changed |= ImGui::DragFloat((prefix + "Bullet Speed").c_str(), &_settings.bulletSpeed, 1.0f, 10.0f, 2000.0f);
        _changed |= ImGui::DragFloat2((prefix + "Bullet Size").c_str(), &_settings.bulletSize.x, 0.1f, 1.0f, 64.0f);
        _changed |= ImGui::DragFloat2((prefix + "Bullet Spawn Offset").c_str(), &_settings.bulletSpawnOffset.x, 0.1f, -200.0f, 200.0f);

        _changed |= ImGui::DragInt((prefix + "Spread Bullet Count").c_str(), &_settings.spreadBulletCount, 1.0f, 1, 64);
        _changed |= ImGui::DragFloat((prefix + "Spread Angle").c_str(), &_settings.spreadAngleDegrees, 0.5f, 0.0f, 360.0f);

        _changed |= ImGui::Checkbox((prefix + "Straight Burst Enabled").c_str(), &_settings.straightBurstEnabled);
        _changed |= ImGui::DragFloat((prefix + "Straight Burst Speed").c_str(), &_settings.straightBurstSpeed, 1.0f, 10.0f, 2000.0f);
        _changed |= ImGui::DragInt((prefix + "Straight Burst Every").c_str(), &_settings.straightBurstEvery, 1.0f, 1, 32);
    }

    void BossComponent::SaveConfig() const
    {
        std::filesystem::create_directories("Assets\\BulletHellChris");

        std::ofstream file("Assets\\BulletHellChris\\bossConfig.txt");
        if (!file.is_open())
        {
            return;
        }

        file << maxHealth << '\n';
        file << hitRadius << '\n';
        file << hitboxOffset.x << ' ' << hitboxOffset.y << '\n';
        file << contactDamage << '\n';
        file << basePosition.x << ' ' << basePosition.y << '\n';

        auto writePhase = [&file](const BossPhaseSettings& settings)
            {
                file << settings.bossScale.x << ' ' << settings.bossScale.y << '\n';
                file << settings.moveAmplitude.x << ' ' << settings.moveAmplitude.y << '\n';
                file << settings.moveFrequency.x << ' ' << settings.moveFrequency.y << '\n';
                file << settings.shootCooldown << '\n';
                file << settings.bulletSpeed << '\n';
                file << settings.bulletSize.x << ' ' << settings.bulletSize.y << '\n';
                file << settings.bulletSpawnOffset.x << ' ' << settings.bulletSpawnOffset.y << '\n';
                file << settings.spreadBulletCount << '\n';
                file << settings.spreadAngleDegrees << '\n';
                file << (settings.straightBurstEnabled ? 1 : 0) << '\n';
                file << settings.straightBurstSpeed << '\n';
                file << settings.straightBurstEvery << '\n';
            };

        writePhase(phase1Settings);
        writePhase(phase2Settings);
        writePhase(phase3Settings);
    }

    void BossComponent::LoadConfig()
    {
        std::ifstream file("Assets\\BulletHellChris\\bossConfig.txt");
        if (!file.is_open())
        {
            return;
        }

        file >> maxHealth;
        file >> hitRadius;

        if (!(file >> hitboxOffset.x >> hitboxOffset.y))
        {
            file.clear();
            hitboxOffset = Maths::Vector2f(0.0f, 0.0f);
            file >> contactDamage;
            file >> basePosition.x >> basePosition.y;
        }
        else
        {
            file >> contactDamage;
            file >> basePosition.x >> basePosition.y;
        }

        auto readPhase = [&file](BossPhaseSettings& settings)
            {
                file >> settings.bossScale.x >> settings.bossScale.y;
                file >> settings.moveAmplitude.x >> settings.moveAmplitude.y;
                file >> settings.moveFrequency.x >> settings.moveFrequency.y;
                file >> settings.shootCooldown;
                file >> settings.bulletSpeed;
                file >> settings.bulletSize.x >> settings.bulletSize.y;
                file >> settings.bulletSpawnOffset.x >> settings.bulletSpawnOffset.y;
                file >> settings.spreadBulletCount;
                file >> settings.spreadAngleDegrees;

                int straightBurstEnabledInt = 0;
                file >> straightBurstEnabledInt;
                settings.straightBurstEnabled = (straightBurstEnabledInt != 0);

                file >> settings.straightBurstSpeed;
                file >> settings.straightBurstEvery;
            };

        readPhase(phase1Settings);
        readPhase(phase2Settings);
        readPhase(phase3Settings);
    }
}