#include "ProjectileComponent.h"
#include "EnemyComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cmath>

namespace TowerDefence {

    void ProjectileComponent::Init(const std::string& name, float dmg, float spd)
    {
        targetName = name;
        damage = dmg;
        speed = spd;
    }

    void ProjectileComponent::Update(float dt)
    {
        if (done) return;

        Scene* scene = GetOwner()->GetScene();
        GameObject* targetObj = scene->FindGameObject(targetName);

        if (!targetObj || targetObj->IsMarkedForDeletion())
        {
            done = true;
            return; // Present() s'occupera de la destruction
        }

        auto* enemy = targetObj->GetComponent<EnemyComponent>();
        if (!enemy || enemy->IsDead() || enemy->IsFinished())
        {
            done = true;
            return;
        }

        Maths::Vector2f pos = GetOwner()->GetPosition();
        Maths::Vector2f tgtPos = targetObj->GetPosition();
        float dx = tgtPos.x - pos.x;
        float dy = tgtPos.y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= speed * dt)
        {
            enemy->TakeDamage(damage); // TakeDamage pose juste un flag, ne détruit rien
            done = true;
        }
        else
        {
            float nx = dx / dist;
            float ny = dy / dist;
            GetOwner()->SetPosition(Maths::Vector2f(
                pos.x + nx * speed * dt,
                pos.y + ny * speed * dt
            ));
        }
    }

    void ProjectileComponent::Present()
    {
        // C'est ici, hors itération, qu'on détruit en sécurité
        if (done)
            GetOwner()->MarkForDeletion();
    }

    void ProjectileComponent::Render(sf::RenderWindow* window)
    {
        if (done) return;

        Maths::Vector2f pos = GetOwner()->GetPosition();
        sf::CircleShape dot(4.f);
        dot.setFillColor(sf::Color::Yellow);
        dot.setOrigin(sf::Vector2f(4.f, 4.f));
        dot.setPosition(sf::Vector2f(pos.x, pos.y));
        window->draw(dot);
    }

}