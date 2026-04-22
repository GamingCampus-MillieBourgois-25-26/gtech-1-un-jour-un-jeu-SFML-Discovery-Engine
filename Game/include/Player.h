Game\include\Player.h

```cpp
#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Components/SquareCollider.h"
#include "Modules/WindowModule.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"

class Player : public Component
{
public:
	void Update(const float _delta_time) override
	{
		// position avant mouvement (pour annuler en cas de collision)
		const Maths::Vector2<float> previousPosition = GetOwner()->GetPosition();
		Maths::Vector2<float> position = previousPosition;

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

		// Clamp dans les limites de la fenêtre en tenant compte de la taille du collider
		SquareCollider* myCollider = GetOwner()->GetComponent<SquareCollider>();
		if (myCollider != nullptr)
		{
			WindowModule* window = GetModule<WindowModule>();
			const Maths::Vector2u windowSize = window->GetSize();

			const float maxX = static_cast<float>(windowSize.x) - myCollider->GetWidth();
			const float maxY = static_cast<float>(windowSize.y) - myCollider->GetHeight();

			if (position.x < 0.f) position.x = 0.f;
			if (position.y < 0.f) position.y = 0.f;
			if (position.x > maxX) position.x = maxX;
			if (position.y > maxY) position.y = maxY;
		}

		// Appliquer position tentée
		GetOwner()->SetPosition(position);

		// Collision avec les autres colliders de la scène -> annuler la position si collision
		if (myCollider != nullptr && GetOwner()->GetScene() != nullptr)
		{
			for (const auto& otherPtr : GetOwner()->GetScene()->GetGameObjects())
			{
				GameObject* other = otherPtr.get();
				if (other == GetOwner())
					continue;

				SquareCollider* otherCollider = other->GetComponent<SquareCollider>();
				if (otherCollider != nullptr && SquareCollider::IsColliding(*myCollider, *otherCollider))
				{
					// En cas de collision on revient à la position précédente
					GetOwner()->SetPosition(previousPosition);
					break;
				}
			}
		}

		if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
		{
			Engine::GetInstance()->RequestQuit();
		}
	}

	float speed = 1000.0f;


};
