#include "BulletHell/Components/PlayerController.h"

#include <fstream>

#include "imgui.h"

#include "InputModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "BulletHell/Components/BulletComponent.h"
#include "BulletHell/BulletHellDebug.h"

namespace bulletHell
{
    void PlayerController::Start()
    {
        LoadConfig();
    }

    void PlayerController::Update(float _delta_time)
    {
        focusMode = InputModule::GetKey(sf::Keyboard::Key::LShift) ||
            InputModule::GetKey(sf::Keyboard::Key::RShift);

        if (dead)
        {
            UpdateHitboxVisual();
            return;
        }

        HandleMovement(_delta_time);
        HandleShoot(_delta_time);
        HandleEnemyBulletCollision(_delta_time);
        ApplyPlayerVisualSize();
        UpdateHitboxVisual();
    }

    void PlayerController::OnGUI()
    {
        if (InputModule::GetKeyDown(sf::Keyboard::Key::F1))
        {
            g_showDebugUI = !g_showDebugUI;
        }

        if (!g_showDebugUI)
        {
            return;
        }

        if (!ImGui::Begin("BulletHell Debug"))
        {
            ImGui::End();
            return;
        }

        bool changed = false;

        ImGui::Text("Player");
        changed |= ImGui::DragFloat("Move Speed", &moveSpeed, 1.0f, 50.0f, 1000.0f);
        changed |= ImGui::DragFloat("Focus Move Speed", &focusMoveSpeed, 1.0f, 20.0f, 600.0f);
        changed |= ImGui::DragFloat2("Player Scale", &playerSize.x, 0.01f, 0.1f, 4.0f);
        changed |= ImGui::DragFloat("Player Hit Radius", &hitRadius, 0.1f, 2.0f, 64.0f);
        changed |= ImGui::DragFloat("Hitbox Visual Size", &hitboxVisualSize, 0.1f, 2.0f, 32.0f);

        ImGui::Separator();

        ImGui::Text("Shoot");
        changed |= ImGui::DragFloat("Shoot Cooldown", &shootCooldown, 0.001f, 0.02f, 1.0f);
        changed |= ImGui::DragFloat("Bullet Speed", &bulletSpeed, 1.0f, 50.0f, 2000.0f);
        changed |= ImGui::DragFloat2("Bullet Size", &bulletSize.x, 0.1f, 2.0f, 64.0f);

        ImGui::Separator();

        ImGui::Text("Bullet Origins");
        changed |= ImGui::DragFloat2("Left Offset", &leftBulletOffset.x, 0.1f, -100.0f, 100.0f);
        changed |= ImGui::DragFloat2("Right Offset", &rightBulletOffset.x, 0.1f, -100.0f, 100.0f);

        ImGui::Separator();

        ImGui::Text("Focus Auto Target");
        changed |= ImGui::Checkbox("Auto Target In Focus", &autoTargetInFocus);
        changed |= ImGui::DragFloat("Auto Target Strength", &autoTargetStrength, 0.01f, 0.0f, 1.0f);

        ImGui::Separator();

        ImGui::Text("Damage / Survival");
        ImGui::Text("Lives: %d", lives);
        ImGui::Text("Focus Mode: %s", focusMode ? "ON" : "OFF");
        ImGui::Text("Invulnerability: %.2f", invulnerabilityTimer);
        changed |= ImGui::DragFloat("Invulnerability Duration", &invulnerabilityDuration, 0.01f, 0.05f, 5.0f);

        if (ImGui::Button("Save Config"))
        {
            SaveConfig();
        }

        ImGui::Text("Pool Size: %d", static_cast<int>(bulletPool.size()));
        ImGui::Text("Enemy Bullet Pool Size: %d", static_cast<int>(enemyBulletPool.size()));

        if (changed)
        {
            SaveConfig();
        }

        ImGui::End();
    }

    void PlayerController::SetBulletPool(const std::vector<GameObject*>& _bulletPool)
    {
        bulletPool = _bulletPool;
        nextBulletIndex = 0;
    }

    void PlayerController::SetEnemyBulletPool(const std::vector<GameObject*>& _enemyBulletPool)
    {
        enemyBulletPool = _enemyBulletPool;
    }

    void PlayerController::SetHitboxObject(GameObject* _hitboxObject)
    {
        hitboxObject = _hitboxObject;
    }

    void PlayerController::SetBossObject(GameObject* _bossObject)
    {
        bossObject = _bossObject;
    }

    int PlayerController::GetLives() const
    {
        return lives;
    }

    bool PlayerController::IsDead() const
    {
        return dead;
    }

    bool PlayerController::IsFocusMode() const
    {
        return focusMode;
    }

    void PlayerController::HandleMovement(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        const float currentMoveSpeed = focusMode ? focusMoveSpeed : moveSpeed;

        Maths::Vector2f position = owner->GetPosition();
        Maths::Vector2f movement = Maths::Vector2f::Zero;

        if (InputModule::GetKey(sf::Keyboard::Key::Q)) movement.x -= 1.0f;
        if (InputModule::GetKey(sf::Keyboard::Key::D)) movement.x += 1.0f;
        if (InputModule::GetKey(sf::Keyboard::Key::Z)) movement.y -= 1.0f;
        if (InputModule::GetKey(sf::Keyboard::Key::S)) movement.y += 1.0f;

        if (movement.MagnitudeSquared() > 0.0f)
        {
            movement = movement.Normalize();
        }

        position += movement * currentMoveSpeed * _delta_time;

        if (position.x < 20.0f) position.x = 20.0f;
        if (position.x > 780.0f) position.x = 780.0f;
        if (position.y < 20.0f) position.y = 20.0f;
        if (position.y > 580.0f) position.y = 580.0f;

        owner->SetPosition(position);
    }

    void PlayerController::HandleShoot(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        if (shootTimer > 0.0f)
        {
            shootTimer -= _delta_time;
        }

        if (!InputModule::GetKey(sf::Keyboard::Key::Space))
        {
            return;
        }

        if (shootTimer > 0.0f)
        {
            return;
        }

        const Maths::Vector2f playerPos = owner->GetPosition();
        const Maths::Vector2f shotDirection = GetFocusedShotDirection();

        FireBulletFromPool(playerPos + leftBulletOffset, shotDirection);
        FireBulletFromPool(playerPos + rightBulletOffset, shotDirection);

        shootTimer = shootCooldown;
    }

    void PlayerController::HandleEnemyBulletCollision(float _delta_time)
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        if (invulnerabilityTimer > 0.0f)
        {
            invulnerabilityTimer -= _delta_time;
            if (invulnerabilityTimer < 0.0f)
            {
                invulnerabilityTimer = 0.0f;
            }
            return;
        }

        const Maths::Vector2f playerPosition = owner->GetPosition();
        const float hitRadiusSquared = hitRadius * hitRadius;

        for (GameObject* bulletObject : enemyBulletPool)
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
            const Maths::Vector2f delta = bulletPosition - playerPosition;
            const float distanceSquared = delta.x * delta.x + delta.y * delta.y;

            if (distanceSquared > hitRadiusSquared)
            {
                continue;
            }

            bulletComponent->Deactivate();
            lives--;
            invulnerabilityTimer = invulnerabilityDuration;

            if (lives <= 0)
            {
                lives = 0;
                dead = true;
            }

            return;
        }
    }

    void PlayerController::FireBulletFromPool(const Maths::Vector2f& _spawnPosition,
        const Maths::Vector2f& _direction)
    {
        if (bulletPool.empty())
        {
            return;
        }

        const int poolSize = static_cast<int>(bulletPool.size());

        for (int i = 0; i < poolSize; ++i)
        {
            GameObject* bulletObject = bulletPool[nextBulletIndex];
            nextBulletIndex = (nextBulletIndex + 1) % poolSize;

            if (bulletObject == nullptr)
            {
                continue;
            }

            BulletComponent* bulletComponent = bulletObject->GetComponent<BulletComponent>();
            if (bulletComponent == nullptr)
            {
                continue;
            }

            if (bulletComponent->IsActive())
            {
                continue;
            }

            bulletObject->SetScale(bulletSize);

            RectangleShapeRenderer* renderer = bulletObject->GetComponent<RectangleShapeRenderer>();
            if (renderer != nullptr)
            {
                renderer->SetSize(bulletSize);
            }

            bulletComponent->Fire(_spawnPosition, _direction, bulletSpeed);
            return;
        }
    }

    Maths::Vector2f PlayerController::GetFocusedShotDirection() const
    {
        const Maths::Vector2f up = { 0.0f, -1.0f };

        if (!focusMode || !autoTargetInFocus || bossObject == nullptr)
        {
            return up;
        }

        if (dead)
        {
            return up;
        }

        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return up;
        }

        Maths::Vector2f toBoss = bossObject->GetPosition() - owner->GetPosition();
        if (toBoss.MagnitudeSquared() <= 0.0001f)
        {
            return up;
        }

        toBoss = toBoss.Normalize();

        Maths::Vector2f blended = up + (toBoss * autoTargetStrength);
        if (blended.MagnitudeSquared() <= 0.0001f)
        {
            return up;
        }

        return blended.Normalize();
    }

    void PlayerController::ApplyPlayerVisualSize()
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr)
        {
            return;
        }

        owner->SetScale(playerSize);
    }

    void PlayerController::UpdateHitboxVisual()
    {
        GameObject* owner = GetOwner();
        if (owner == nullptr || hitboxObject == nullptr)
        {
            return;
        }

        hitboxObject->SetPosition(owner->GetPosition());

        RectangleShapeRenderer* renderer = hitboxObject->GetComponent<RectangleShapeRenderer>();
        if (renderer != nullptr)
        {
            if (focusMode && !dead)
            {
                renderer->SetSize({ hitboxVisualSize, hitboxVisualSize });
                renderer->SetColor(sf::Color::White);
            }
            else
            {
                renderer->SetSize({ 0.0f, 0.0f });
            }
        }
    }

    void PlayerController::SaveConfig() const
    {
        std::ofstream file("player_config.txt");
        if (!file.is_open())
        {
            return;
        }

        file << moveSpeed << "\n";
        file << focusMoveSpeed << "\n";
        file << shootCooldown << "\n";
        file << bulletSpeed << "\n";

        file << playerSize.x << " " << playerSize.y << "\n";
        file << bulletSize.x << " " << bulletSize.y << "\n";

        file << leftBulletOffset.x << " " << leftBulletOffset.y << "\n";
        file << rightBulletOffset.x << " " << rightBulletOffset.y << "\n";

        file << hitRadius << "\n";
        file << invulnerabilityDuration << "\n";
        file << hitboxVisualSize << "\n";
        file << autoTargetInFocus << "\n";
        file << autoTargetStrength << "\n";
    }

    void PlayerController::LoadConfig()
    {
        std::ifstream file("player_config.txt");
        if (!file.is_open())
        {
            return;
        }

        float loadedMoveSpeed = moveSpeed;
        float loadedFocusMoveSpeed = focusMoveSpeed;
        float loadedShootCooldown = shootCooldown;
        float loadedBulletSpeed = bulletSpeed;

        Maths::Vector2f loadedPlayerSize = playerSize;
        Maths::Vector2f loadedBulletSize = bulletSize;

        Maths::Vector2f loadedLeftOffset = leftBulletOffset;
        Maths::Vector2f loadedRightOffset = rightBulletOffset;

        float loadedHitRadius = hitRadius;
        float loadedInvulnerabilityDuration = invulnerabilityDuration;
        float loadedHitboxVisualSize = hitboxVisualSize;

        bool loadedAutoTargetInFocus = autoTargetInFocus;
        float loadedAutoTargetStrength = autoTargetStrength;

        if (!(file >> loadedMoveSpeed)) return;
        if (!(file >> loadedFocusMoveSpeed)) return;
        if (!(file >> loadedShootCooldown)) return;
        if (!(file >> loadedBulletSpeed)) return;

        if (!(file >> loadedPlayerSize.x >> loadedPlayerSize.y)) return;
        if (!(file >> loadedBulletSize.x >> loadedBulletSize.y)) return;

        if (!(file >> loadedLeftOffset.x >> loadedLeftOffset.y)) return;
        if (!(file >> loadedRightOffset.x >> loadedRightOffset.y)) return;

        if (!(file >> loadedHitRadius)) return;
        if (!(file >> loadedInvulnerabilityDuration)) return;
        if (!(file >> loadedHitboxVisualSize)) return;

        if (!(file >> loadedAutoTargetInFocus)) return;
        if (!(file >> loadedAutoTargetStrength)) return;

        moveSpeed = loadedMoveSpeed;
        focusMoveSpeed = loadedFocusMoveSpeed;
        shootCooldown = loadedShootCooldown;
        bulletSpeed = loadedBulletSpeed;

        playerSize = loadedPlayerSize;
        bulletSize = loadedBulletSize;

        leftBulletOffset = loadedLeftOffset;
        rightBulletOffset = loadedRightOffset;

        hitRadius = loadedHitRadius;
        invulnerabilityDuration = loadedInvulnerabilityDuration;
        hitboxVisualSize = loadedHitboxVisualSize;

        autoTargetInFocus = loadedAutoTargetInFocus;
        autoTargetStrength = loadedAutoTargetStrength;

        if (shootCooldown < 0.01f || shootCooldown > 2.0f)
        {
            shootCooldown = 0.10f;
        }

        if (bulletSpeed < 50.0f || bulletSpeed > 5000.0f)
        {
            bulletSpeed = 700.0f;
        }

        if (focusMoveSpeed < 10.0f || focusMoveSpeed > 1000.0f)
        {
            focusMoveSpeed = 120.0f;
        }

        if (moveSpeed < 10.0f || moveSpeed > 2000.0f)
        {
            moveSpeed = 280.0f;
        }

        if (autoTargetStrength < 0.0f || autoTargetStrength > 1.0f)
        {
            autoTargetStrength = 0.35f;
        }
    }
} 