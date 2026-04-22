#pragma once
#include "Core/Component.h"
#include "Core/Scene.h"
#include "FPlayer.h"
#include <cmath>
#include <iostream>
class Bullet : public Component
{
public:
    Maths::Vector2f velocity;
    bool active = false;

    void Activate(const Maths::Vector2f& pos, const Maths::Vector2f& vel)
    {
        active = true;
        velocity = vel;
        GetOwner()->SetPosition(pos);
    }

    void Deactivate()
    {
        active = false;
        GetOwner()->SetPosition(Maths::Vector2f(-1000.f, -1000.f));
    }

    void Update(float _delta_time) override
    {
        if (!active) return;

        auto pos = GetOwner()->GetPosition();
        pos = pos + velocity * _delta_time;
        GetOwner()->SetPosition(pos);

        //COLLISION CHECK
        Scene* scene = GetOwner()->GetScene();

        for (auto& obj: scene->GetGameObjects()) // adapte si ton engine a un autre système
        {
            if (obj->GetName() == "Player")
            {
                FPlayer* player = obj->GetComponent<FPlayer>();
                if (!player) continue;

                Maths::Vector2f diff = pos - obj->GetPosition();
                float dist2 = diff.x * diff.x + diff.y * diff.y;
                float radius = player->radius + 3.f; // bullet radius

                if (dist2 < radius * radius)
                {
                    std::cout << "HIT PLAYER!\n";

                    Deactivate();
                    return;
                }
            }
        }

        // hors écran
        if (pos.x < -100 || pos.x > 2000 || pos.y < -100 || pos.y > 2000)
        {
            Deactivate();
        }
    }
};