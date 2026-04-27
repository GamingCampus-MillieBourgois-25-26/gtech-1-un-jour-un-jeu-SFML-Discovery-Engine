#include "BulletHell/Bullet.h"
#include "Engine.h"

Bullet::Bullet(Maths::Vector2f _direction, float _speed)
    : direction(_direction), speed(_speed)
{
}

void Bullet::Start()
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* texture = assets_module->LoadAsset<Texture>("googly-" + std::to_string(RandomInt(1, 2)) + ".png");
    GetOwner()->CreateComponent<SpriteRenderer>(texture);
}

void Bullet::Update(float _delta_time)
{
    Maths::Vector2f pos = GetOwner()->GetPosition();
    pos.x += direction.x * speed * _delta_time;
    pos.y += direction.y * speed * _delta_time;
    GetOwner()->SetPosition(pos);

    const auto window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();

    if (pos.x < -50 || pos.x > window_size.x + 50 ||
        pos.y < -50 || pos.y > window_size.y + 50)
    {
        GetOwner()->MarkForDeletion();
    }
}