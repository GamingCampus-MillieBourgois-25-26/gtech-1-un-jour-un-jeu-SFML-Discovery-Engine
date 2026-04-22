#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "SquareCollider.h"
#include "Bullet.h"
#include <memory>

namespace BulletHell
{
	class Enemy : public Component
	{
	private:
		sf::Clock cooldown;
		float positionX;
		float positionY;
	public:
		Enemy(float _positionX, float _positionY)
		{
			positionX = _positionX;
			positionY = _positionY;
		}

		void Start() override {
			cooldown.restart();
			GetOwner()->SetPosition({ positionX, positionY });
		}

		void Update(const float _delta_time) override
		{
			if (cooldown.getElapsedTime().asSeconds() >= 10000.1f) {
				Logger::Log(ELogLevel::Debug, "Bullet ennemi tirer");
				cooldown.restart();
			}
		}

		float speed = 250.0f;
	};
}