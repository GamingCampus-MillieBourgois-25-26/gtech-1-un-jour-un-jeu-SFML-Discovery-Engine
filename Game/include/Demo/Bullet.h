#pragma once

#include "Core\Component.h"
#include <SquareCollider.h>
#include <RectangleShapeRenderer.h>
#include "Scene.h"

namespace BulletHell {

class Bullet : public Component
{
private:
	float positionX;
	float positionY;

	float speedBullet = 100.f;
	int bulletCount = 0;
public:

	~Bullet() {
		bulletCount--;
	}

	Bullet(float _speedBullet, float _positionX, float _positionY) {
		speedBullet = _speedBullet;
		positionX = _positionX;
		positionY = _positionY;
	}

	void Update(const float _delta_time) override;

	void ShouldCreateBullet() {
		if (bulletCount <= 100)
		{
			Logger::Log(ELogLevel::Debug, "Shoot avec succes");

			// GameObject* bullet = CreateGameObject("Bullet");
			// SquareCollider* square_collider = bullet->CreateComponent<SquareCollider>();
			//square_collider->SetWidth(40.f);
			//square_collider->SetHeight(20.f);

			//RectangleShapeRenderer* shape_renderer = bullet->CreateComponent<RectangleShapeRenderer>();
			//shape_renderer->SetColor(sf::Color::Green);
			//shape_renderer->SetSize(Maths::Vector2f(40.f, 20.f));

			//bullet->CreateComponent<Bullet>(100.f, 400.f, 400.f);
		}
	}
};
}
