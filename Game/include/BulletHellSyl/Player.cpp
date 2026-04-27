#include "Player.h"
#include "Modules/WindowModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "Core/Scene.h"
#include "Components/SquareCollider.h"
#include "BulletHellSyl/EndGame.h"
#include <iostream>
#include <string>

Player::Player()
{
    window_size = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetSize();
}

void Player::Update(const float _delta_time)
{
    invunerabilityTime += _delta_time;
    Maths::Vector2<float> position = GetOwner()->GetPosition();

    if (InputModule::GetKey(sf::Keyboard::Key::D))
    {
        if(position.x + 19.f < window_size.x)
            position.x += speed * _delta_time;
    }
    if (InputModule::GetKey(sf::Keyboard::Key::Q))
    {
        if (position.x - 19.f > 0)
            position.x -= speed * _delta_time;
    }

    if (InputModule::GetKey(sf::Keyboard::Key::Z))
    {
        if (position.y - 14.f > 0)
            position.y -= speed * _delta_time;
    }
    if (InputModule::GetKey(sf::Keyboard::Key::S))
    {
        if (position.y + 14.f < window_size.y)
            position.y += speed * _delta_time;
    }
    if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
    {
        Engine::GetInstance()->RequestQuit();
    }

    GetOwner()->SetPosition(position);
    if (CheckCollision())
    {
        if (invunerabilityTime >= 1.f)
        {
            invunerabilityTime = 0.f;
            if (life > 0)
            {
                life--;
                UpdateDisplayer();
                if (life == 0)
                {
                    const auto& objects = GetOwner()->GetScene()->GetGameObjects();
                    for (const auto& object : objects)
                    {
                        GameObject* obj = object.get();
                        if (!obj || obj->IsMarkedForDeletion())
                            continue;
                        else if (obj->GetName() == "EndDisplay")
                        {
                            obj->GetComponent<EndGame>()->End(false);
                        }
                    }
                }
            }
        }
    }
    if (lifeDisplayer == nullptr)
        CreateDisplayer();
}

void Player::UpdateDisplayer()
{
    if (lifeDisplayer)
    {
        lifeDisplayer->MarkForDeletion();
        lifeDisplayer = nullptr;
    }
    CreateDisplayer();
}

void Player::CreateDisplayer()
{
    std::string string = std::to_string(life);
    lifeDisplayer = GetOwner()->GetScene()->CreateGameObject("life");
    TextRenderer* text = lifeDisplayer->CreateComponent<TextRenderer>("life: " + string + "/3");
    text->SetColor(sf::Color::White);
}

bool Player::CheckCollision()
{
    Maths::Vector2f pos = GetOwner()->GetPosition();
    const auto& objects = GetOwner()->GetScene()->GetGameObjects();
    for (const auto& objPtr : objects)
    {
        GameObject* obj = objPtr.get();
        if (!obj || obj->IsMarkedForDeletion())
            continue;
        if (obj->GetName() == "bullet")
        {
            if (SquareCollider::IsColliding(*GetOwner()->GetComponent<SquareCollider>(), *obj->GetComponent<SquareCollider>()))
            {
                return true;
            }
        }
    }
    return false;
}