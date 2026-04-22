#include "BulletHell/Components/BossComponent.h"

#include <cmath>
#include <fstream>

#include "imgui.h"

#include "Components/RectangleShapeRenderer.h"
#include "BulletHell/Components/BulletComponent.h"

namespace bulletHell
{
    void BossComponent::Start()
    {
        phase1Settings.bossScale = Maths::Vector2f(1.0f, 1.0f);
        phase1Settings.moveAmplitude = Maths::Vector2f(120.0f, 0.0f);
        phase1Settings.moveFrequency = Maths::Vector2f(1.0f, 0.0f);
        phase1Settings.shootCooldown = 0.45f;
        phase1Settings.bulletSpeed = 180.0f;
        phase1Settings.bulletSize = Maths::Vector2f(10.0f, 10.0f);
        phase1Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 28.0f);
        phase1Settings.spreadBulletCount = 5;
        phase1Settings.spreadAngleDegrees = 40.0f;
        phase1Settings.straightBurstEnabled = false;
        phase1Settings.straightBurstSpeed = 280.0f;
        phase1Settings.straightBurstEvery = 2;

        phase2Settings.bossScale = Maths::Vector2f(1.0f, 1.0f);
        phase2Settings.moveAmplitude = Maths::Vector2f(180.0f, 20.0f);
        phase2Settings.moveFrequency = Maths::Vector2f(1.8f, 0.8f);
        phase2Settings.shootCooldown = 0.30f;
        phase2Settings.bulletSpeed = 220.0f;
        phase2Settings.bulletSize = Maths::Vector2f(10.0f, 10.0f);
        phase2Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 28.0f);
        phase2Settings.spreadBulletCount = 7;
        phase2Settings.spreadAngleDegrees = 70.0f;
        phase2Settings.straightBurstEnabled = false;
        phase2Settings.straightBurstSpeed = 300.0f;
        phase2Settings.straightBurstEvery = 2;

        phase3Settings.bossScale = Maths::Vector2f(1.0f, 1.0f);
        phase3Settings.moveAmplitude = Maths::Vector2f(220.0f, 40.0f);
        phase3Settings.moveFrequency = Maths::Vector2f(2.5f, 1.7f);
        phase3Settings.shootCooldown = 0.20f;
        phase3Settings.bulletSpeed = 260.0f;
        phase3Settings.bulletSize = Maths::Vector2f(10.0f, 10.0f);
        phase3Settings.bulletSpawnOffset = Maths::Vector2f(0.0f, 28.0f);
        phase3Settings.spreadBulletCount = 9;
        phase3Settings.spreadAngleDegrees = 100.0f;
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

        if (currentHealth <= 0.0f)
        {
            currentHealth = 0.0f;
            defeated = true;
        }
    }

    void BossComponent::HandleMovement(float)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        const BossPhaseSettings& settings = GetCurrentPhaseSettings();

        Maths::Vector2f position = basePosition;
        position.x += std::sin(movementTimer * settings.moveFrequency.x) * settings.moveAmplitude.x;
        position.y += std::sin(movementTimer * settings.moveFrequency.y) * settings.moveAmplitude.y;

        owner->SetPosition(position);
    }

    void BossComponent::HandleShoot(float _delta_time)
    {
        if (shootTimer > 0.0f)
        {
            shootTimer -= _delta_time;
        }

        if (shootTimer > 0.0f)
        {
            return;
        }

        const BossPhaseSettings& settings = GetCurrentPhaseSettings();

        FireSpread(settings);

        phaseBurstCounter++;
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

        const Maths::Vector2f bossPosition = owner->GetPosition();
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

            const Maths::Vector2f bulletPosition = bulletObject->GetPosition();
            const Maths::Vector2f delta = bulletPosition - bossPosition;
            const float distanceSquared = delta.x * delta.x + delta.y * delta.y;

            if (distanceSquared > hitRadiusSquared)
            {
                continue;
            }

            currentHealth -= contactDamage;
            bulletComponent->Deactivate();

            if (currentHealth <= 0.0f)
            {
                currentHealth = 0.0f;
                defeated = true;
                return;
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

        const int poolSize = static_cast<int>(enemyBullets.size());

        for (int i = 0; i < poolSize; ++i)
        {
            GameObject* bulletObject = enemyBullets[nextEnemyBulletIndex];
            nextEnemyBulletIndex = (nextEnemyBulletIndex + 1) % poolSize;

            if (bulletObject == nullptr)
            {
                continue;
            }

            BulletComponent* bulletComponent = bulletObject->GetComponent<BulletComponent>();
            if (bulletComponent == nullptr || bulletComponent->IsActive())
            {
                continue;
            }

            RectangleShapeRenderer* renderer = bulletObject->GetComponent<RectangleShapeRenderer>();
            if (renderer != nullptr)
            {
                renderer->SetColor(sf::Color(255, 110, 110));
                renderer->SetSize(_bulletSize);
            }

            bulletObject->SetScale(_bulletSize);

            const Maths::Vector2f spawnPosition = owner->GetPosition() + _spawnOffset;
            bulletComponent->Fire(spawnPosition, _direction, _speed);
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
    }

    Maths::Vector2f BossComponent::RotateVectorDegrees(const Maths::Vector2f& _vector, float _degrees) const
    {
        constexpr float pi = 3.14159265359f;
        const float radians = _degrees * pi / 180.0f;

        const float cosAngle = std::cos(radians);
        const float sinAngle = std::sin(radians);

        return Maths::Vector2f(
            _vector.x * cosAngle - _vector.y * sinAngle,
            _vector.x * sinAngle + _vector.y * cosAngle
        );
    }

    BossPhaseSettings& BossComponent::GetCurrentPhaseSettings()
    {
        if (phase == 1) return phase1Settings;
        if (phase == 2) return phase2Settings;
        return phase3Settings;
    }

    const BossPhaseSettings& BossComponent::GetCurrentPhaseSettings() const
    {
        if (phase == 1) return phase1Settings;
        if (phase == 2) return phase2Settings;
        return phase3Settings;
    }

    void BossComponent::DrawPhaseSettingsGUI(const char* _label, BossPhaseSettings& _settings, bool& _changed)
    {
        if (!ImGui::TreeNode(_label))
        {
            return;
        }

        _changed |= ImGui::DragFloat2("Boss Scale", &_settings.bossScale.x, 0.01f, 0.1f, 5.0f);
        _changed |= ImGui::DragFloat2("Move Amplitude", &_settings.moveAmplitude.x, 1.0f, 0.0f, 600.0f);
        _changed |= ImGui::DragFloat2("Move Frequency", &_settings.moveFrequency.x, 0.01f, 0.0f, 10.0f);

        _changed |= ImGui::DragFloat("Shoot Cooldown", &_settings.shootCooldown, 0.01f, 0.02f, 3.0f);
        _changed |= ImGui::DragFloat("Bullet Speed", &_settings.bulletSpeed, 1.0f, 10.0f, 2000.0f);
        _changed |= ImGui::DragFloat2("Bullet Size", &_settings.bulletSize.x, 0.1f, 1.0f, 64.0f);
        _changed |= ImGui::DragFloat2("Bullet Spawn Offset", &_settings.bulletSpawnOffset.x, 0.1f, -200.0f, 200.0f);

        _changed |= ImGui::DragInt("Spread Count", &_settings.spreadBulletCount, 1.0f, 1, 64);
        _changed |= ImGui::DragFloat("Spread Angle", &_settings.spreadAngleDegrees, 0.5f, 0.0f, 180.0f);

        _changed |= ImGui::Checkbox("Straight Burst Enabled", &_settings.straightBurstEnabled);
        _changed |= ImGui::DragFloat("Straight Burst Speed", &_settings.straightBurstSpeed, 1.0f, 10.0f, 2000.0f);
        _changed |= ImGui::DragInt("Straight Burst Every", &_settings.straightBurstEvery, 1.0f, 1, 20);

        ImGui::TreePop();
    }

    void BossComponent::SaveConfig() const
    {
        std::ofstream file("boss_config.txt");
        if (!file.is_open())
        {
            return;
        }

        file << maxHealth << "\n";
        file << hitRadius << "\n";
        file << contactDamage << "\n";
        file << basePosition.x << " " << basePosition.y << "\n";

        const BossPhaseSettings* phases[3] = { &phase1Settings, &phase2Settings, &phase3Settings };

        for (int i = 0; i < 3; ++i)
        {
            const BossPhaseSettings& p = *phases[i];

            file << p.bossScale.x << " " << p.bossScale.y << "\n";
            file << p.moveAmplitude.x << " " << p.moveAmplitude.y << "\n";
            file << p.moveFrequency.x << " " << p.moveFrequency.y << "\n";
            file << p.shootCooldown << "\n";
            file << p.bulletSpeed << "\n";
            file << p.bulletSize.x << " " << p.bulletSize.y << "\n";
            file << p.bulletSpawnOffset.x << " " << p.bulletSpawnOffset.y << "\n";
            file << p.spreadBulletCount << "\n";
            file << p.spreadAngleDegrees << "\n";
            file << p.straightBurstEnabled << "\n";
            file << p.straightBurstSpeed << "\n";
            file << p.straightBurstEvery << "\n";
        }
    }

    void BossComponent::LoadConfig()
    {
        std::ifstream file("boss_config.txt");
        if (!file.is_open())
        {
            return;
        }

        if (!(file >> maxHealth)) return;
        if (!(file >> hitRadius)) return;
        if (!(file >> contactDamage)) return;
        if (!(file >> basePosition.x >> basePosition.y)) return;

        BossPhaseSettings* phases[3] = { &phase1Settings, &phase2Settings, &phase3Settings };

        for (int i = 0; i < 3; ++i)
        {
            BossPhaseSettings& p = *phases[i];

            if (!(file >> p.bossScale.x >> p.bossScale.y)) return;
            if (!(file >> p.moveAmplitude.x >> p.moveAmplitude.y)) return;
            if (!(file >> p.moveFrequency.x >> p.moveFrequency.y)) return;
            if (!(file >> p.shootCooldown)) return;
            if (!(file >> p.bulletSpeed)) return;
            if (!(file >> p.bulletSize.x >> p.bulletSize.y)) return;
            if (!(file >> p.bulletSpawnOffset.x >> p.bulletSpawnOffset.y)) return;
            if (!(file >> p.spreadBulletCount)) return;
            if (!(file >> p.spreadAngleDegrees)) return;
            if (!(file >> p.straightBurstEnabled)) return;
            if (!(file >> p.straightBurstSpeed)) return;
            if (!(file >> p.straightBurstEvery)) return;
        }
    }
}