#include "Player.h"
#include "Modules/WindowModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "Core/Scene.h"
#include "Components/SquareCollider.h"
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
        if(position.x < window_size.x)
            position.x += speed * _delta_time;
    }
    if (InputModule::GetKey(sf::Keyboard::Key::Q))
    {
        if (position.x > 0)
            position.x -= speed * _delta_time;
    }

    if (InputModule::GetKey(sf::Keyboard::Key::Z))
    {
        if (position.y > 0)
            position.y -= speed * _delta_time;
    }
    if (InputModule::GetKey(sf::Keyboard::Key::S))
    {
        if (position.y < window_size.y)
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
    GameObject* owner = GetOwner();
    Maths::Vector2f pos = owner->GetPosition();

    const auto& objects = owner->GetScene()->GetGameObjects();

    for (const auto& objPtr : objects)
    {
        GameObject* obj = objPtr.get();

        if (!obj || obj->IsMarkedForDeletion())
            continue;
        if (obj->GetName().find("bullet") == std::string::npos)
            continue;
        auto posObj = obj->GetPosition();
        SquareCollider* playerCol = GetOwner()->GetComponent<SquareCollider>();
        SquareCollider* bulletCol = obj->GetComponent<SquareCollider>();
        if(SquareCollider::IsColliding(*playerCol, *bulletCol))
            return true;

    }
    return false;
}