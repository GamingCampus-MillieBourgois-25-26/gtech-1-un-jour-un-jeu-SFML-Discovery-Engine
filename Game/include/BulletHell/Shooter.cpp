#include "Shooter.h"
#include "BulletHell/Shooter.h"
#include "BulletHell/Bullet.h"
#include "Core/GameObject.h"
#include "Assets/Texture.h"
#include "Core/Scene.h"
#include "Engine.h"
#include <numbers>

void Shooter::Update(float _delta_time)
{
    timer += _delta_time;

    if (inPause)
    {
        if (timer >= pauseBetweenBursts)
        {
            timer = 0.f;
            wavesShot = 0;
            inPause = false;
        }
        return;
    }

    if (timer >= timeBetweenWaves)
    {
        timer = 0.f;
        SpawnWave();
        wavesShot++;

        if (wavesShot >= wavesPerBurst)
            inPause = true;
    }
}

void Shooter::SpawnWave()
{
    Scene* scene = owner->GetScene();
    const Maths::Vector2f origin = GetOwner()->GetPosition();

    const float angleStep = (2.f * std::numbers::pi_v<float>) / bulletsPerBurst;

    // Décalage de la vague pour l'effet "vague sinusoïdale"
    const float waveOffset = wavesShot * (angleStep / 2.f);

    for (int i = 0; i < bulletsPerBurst; ++i)
    {
        const float angle = i * angleStep + waveOffset;

        Maths::Vector2f dir(std::cos(angle), std::sin(angle));

        GameObject* bulletGO = scene->CreateGameObject("Bullet");
        bulletGO->SetPosition(origin);
        bulletGO->CreateComponent<Bullet>(dir, bulletSpeed);
        
    }
}