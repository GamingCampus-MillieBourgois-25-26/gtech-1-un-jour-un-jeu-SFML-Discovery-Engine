#pragma once
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Components/SpriteRenderer.h"  
#include "Assets/Texture.h"             
#include "Modules/AssetsModule.h"     
#include "Modules/WindowModule.h"       
#include <chrono>
#include <cstdint>
#include <random>
#include <string>
class Bullet : public Component
{
public:
    Bullet(Maths::Vector2f _direction, float _speed = 200.f);

    void Start() override;
    void Update(float _delta_time) override;
    

private:
    Maths::Vector2f direction;
    float speed;

    int RandomInt(const int _min, const int _max)
    {
        thread_local std::mt19937_64 gen(static_cast<uint64_t>(
            std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<int> dist(_min, _max);
        return dist(gen);
    }
};