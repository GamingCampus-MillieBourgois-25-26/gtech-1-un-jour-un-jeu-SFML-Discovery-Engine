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
    Maths::Vector2f pos = GetOwner()->GetPosition();
    const auto& objects = GetOwner()->GetScene()->GetGameObjects();

    for (const auto& objPtr : objects)
    {
        GameObject* obj = objPtr.get();

        if (!obj || obj->IsMarkedForDeletion())
            continue;
        /*if (obj->GetName().find("bullet") == std::string::npos)
            continue;*/
        if (obj->GetName() == "bullet")
        {
            auto posObj = obj->GetPosition();
            //auto sizeObj = obj->GetComponent<RectangleShapeRenderer>()->GetSize();
            auto pos = GetOwner()->GetPosition();
            pos.x -= 40.f;
            posObj.x -= 40.f;
            //auto size = GetOwner()->GetComponent<RectangleShapeRenderer>()->GetSize();
            /*if (pos.x < posObj.x + (sizeObj.x/2) && pos.x + (size.x/2) > posObj.x &&
                pos.y < posObj.y + (sizeObj.y/2) && pos.y + (size.y/2) > posObj.y )
            {*/
            if (pos.x < posObj.x + 20.f && pos.x + 25.f > posObj.x &&
                pos.y < posObj.y + 20.f && pos.y + 25.f > posObj.y )
            {
                return true;
            }
        }

    }
    return false;
}