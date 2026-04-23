#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Bullet.h"

namespace Demo
{
    class Player : public Component
    {
    public:
        Maths::Vector2f angle;
        void Update(const float _delta_time) override
        {
            
            Maths::Vector2i mouse_position = InputModule::GetMousePosition();
            Maths::Vector2<float> position = GetOwner()->GetPosition();
            Maths::Vector2<float> mouseFloat(
                static_cast<float>(mouse_position.x),
                static_cast<float>(mouse_position.y)
            );
            angle = mouseFloat - position;
            float a = atan2(angle.y, angle.x);
           

            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                position.x += speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                position.x -= speed * _delta_time;
            }

            if (InputModule::GetKey(sf::Keyboard::Key::Z))
            {
                position.y -= speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::S))
            {
                position.y += speed * _delta_time;
            }

            if (InputModule::GetMouseButton(sf::Mouse::Button::Left)) {

            }

            GetOwner()->SetPosition(position);
            GetOwner()->SetRotation(sf::radians(a));

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }
        }

        float speed = 100.0f;
    };

}
