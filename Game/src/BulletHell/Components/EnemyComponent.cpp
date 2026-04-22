#include "BulletHell/Components/EnemyComponent.h"

#include <cmath>
#include <filesystem>
#include <fstream>

#include "imgui.h"

#include "BulletHell/BulletHellDebug.h"
#include "BulletHell/Components/BulletComponent.h"

namespace bulletHell
{
    void EnemyComponent::Start()
    {
        LoadConfig();
    }

    void EnemyComponent::Update(float _delta_time)
    {
        HandleMovement(_delta_time);
        HandleShoot(_delta_time);
    }

    void EnemyComponent::OnGUI()
    {
        if (!g_showDebugUI)
        {
            return;
        }

        if (!ImGui::Begin("Enemy Debug"))
        {
            ImGui::End();
            return;
        }

        bool changed = false;

        ImGui::Text("Movement");
        changed |= ImGui::DragFloat2("Enemy Target", &targetPosition.x, 1.0f, 0.0f, 800.0f);
        changed |= ImGui::DragFloat("Enemy Move Speed", &moveSpeed, 1.0f, 0.0f, 1000.0f);

        ImGui::Separator();

        ImGui::Text("Shoot");
        changed |= ImGui::DragFloat("Enemy Shoot Cooldown", &shootCooldown, 0.01f, 0.05f, 2.0f);
        changed |= ImGui::DragFloat("Enemy Bullet Speed", &bulletSpeed, 1.0f, 10.0f, 1000.0f);
        changed |= ImGui::DragFloat2("Enemy Bullet Size", &bulletSize.x, 0.1f, 1.0f, 64.0f);
        changed |= ImGui::DragFloat2("Enemy Spawn Offset", &bulletSpawnOffset.x, 0.1f, -100.0f, 100.0f);

        ImGui::Separator();

        ImGui::Text("Spread Pattern");
        changed |= ImGui::DragInt("Spread Bullet Count", &spreadBulletCount, 1.0f, 1, 32);
        changed |= ImGui::DragFloat("Spread Angle", &spreadAngleDegrees, 0.5f, 0.0f, 180.0f);

        ImGui::Separator();

        if (ImGui::Button("Save Enemy Config"))
        {
            SaveConfig();
        }

        ImGui::SameLine();

        if (ImGui::Button("Load Enemy Config"))
        {
            LoadConfig();
        }

        ImGui::Text("Enemy Bullet Pool: %d", static_cast<int>(bulletPool.size()));

        if (changed)
        {
            SaveConfig();
        }

        ImGui::End();
    }

    void EnemyComponent::SetBulletPool(const std::vector<GameObject*>& _bulletPool)
    {
        bulletPool = _bulletPool;
        nextBulletIndex = 0;
    }

    void EnemyComponent::HandleMovement(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        if (reachedTarget)
        {
            return;
        }

        Maths::Vector2f position = owner->GetPosition();
        Maths::Vector2f toTarget = targetPosition - position;

        if (toTarget.MagnitudeSquared() < 4.0f)
        {
            owner->SetPosition(targetPosition);
            reachedTarget = true;
            return;
        }

        Maths::Vector2f direction = toTarget.Normalize();
        position += direction * moveSpeed * _delta_time;
        owner->SetPosition(position);
    }

    void EnemyComponent::HandleShoot(float _delta_time)
    {
        if (!reachedTarget)
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

        if (spreadBulletCount <= 1)
        {
            FireBulletFromPool({ 0.0f, 1.0f });
            shootTimer = shootCooldown;
            return;
        }

        const float startAngle = -spreadAngleDegrees * 0.5f;
        const float stepAngle = spreadAngleDegrees / static_cast<float>(spreadBulletCount - 1);

        for (int i = 0; i < spreadBulletCount; ++i)
        {
            const float angle = startAngle + stepAngle * static_cast<float>(i);
            const Maths::Vector2f direction = RotateVectorDegrees({ 0.0f, 1.0f }, angle);
            FireBulletFromPool(direction);
        }

        shootTimer = shootCooldown;
    }

    void EnemyComponent::FireBulletFromPool(const Maths::Vector2f& _direction)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr || bulletPool.empty())
        {
            return;
        }

        const std::size_t poolSize = bulletPool.size();
        for (std::size_t i = 0; i < poolSize; ++i)
        {
            GameObject* bulletObject = bulletPool[nextBulletIndex];
            nextBulletIndex = (nextBulletIndex + 1) % static_cast<int>(poolSize);

            if (bulletObject == nullptr)
            {
                continue;
            }

            BulletComponent* bulletComponent = bulletObject->GetComponent<BulletComponent>();
            if (bulletComponent == nullptr || bulletComponent->IsActive())
            {
                continue;
            }

            bulletObject->SetPosition(owner->GetPosition() + bulletSpawnOffset);
            bulletComponent->Activate(_direction, bulletSpeed, bulletSize);
            return;
        }
    }

    Maths::Vector2f EnemyComponent::RotateVectorDegrees(const Maths::Vector2f& _vector, float _degrees) const
    {
        const float radians = _degrees * 3.14159265f / 180.0f;
        const float cosAngle = std::cos(radians);
        const float sinAngle = std::sin(radians);

        return
        {
            _vector.x * cosAngle - _vector.y * sinAngle,
            _vector.x * sinAngle + _vector.y * cosAngle
        };
    }

    void EnemyComponent::SaveConfig() const
    {
        std::filesystem::create_directories("Assets\\BulletHellChris");

        std::ofstream file("Assets\\BulletHellChris\\bulletHellEnemyConfig.txt");
        if (!file.is_open())
        {
            return;
        }

        file << targetPosition.x << ' ' << targetPosition.y << '\n';
        file << moveSpeed << '\n';
        file << shootCooldown << '\n';
        file << bulletSpeed << '\n';
        file << bulletSize.x << ' ' << bulletSize.y << '\n';
        file << bulletSpawnOffset.x << ' ' << bulletSpawnOffset.y << '\n';
        file << spreadBulletCount << '\n';
        file << spreadAngleDegrees << '\n';
    }

    void EnemyComponent::LoadConfig()
    {
        std::ifstream file("Assets\\BulletHellChris\\bulletHellEnemyConfig.txt");
        if (!file.is_open())
        {
            return;
        }

        file >> targetPosition.x >> targetPosition.y;
        file >> moveSpeed;
        file >> shootCooldown;
        file >> bulletSpeed;
        file >> bulletSize.x >> bulletSize.y;
        file >> bulletSpawnOffset.x >> bulletSpawnOffset.y;
        file >> spreadBulletCount;
        file >> spreadAngleDegrees;
    }
}