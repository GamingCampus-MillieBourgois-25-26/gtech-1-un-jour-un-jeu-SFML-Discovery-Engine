#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <cmath>

class Shooter : public Component
{
public:
    // Paramètres du pattern
    int   bulletsPerBurst = 8;
    int   wavesPerBurst = 3; 
    float timeBetweenWaves = 0.15f; 
    float pauseBetweenBursts = 2.f;  

    void Update(float _delta_time) override;

private:
    void SpawnWave();
    GameObject* owner = GetOwner();
    float timer = 0.f;
    int   wavesShot = 0;
    bool  inPause = false;
    float bulletSpeed = 200.0f;
};