#pragma once
#include "Component.h"
#include <SpriteRenderer.h>
#include "Scene.h"

namespace TowerDefense
{
	class Enemy : public Component
	{
	private:
		float speed;
		int health;
		int damage;
		int coin; // Nombre de pièce donné quand il meurt.
		bool pointsReached[5] = {false, false, false, false, false};

		std::vector<sf::Vector2f> enemyPosition;

	public:
		Enemy(float _speed, int _health, int _damage, int _coin);

		void Update(float _delta_time) override;
		void MovementPattern(GameObject* target, float targetPositionX, float targetPositionY, float _delta_time);
	};
}