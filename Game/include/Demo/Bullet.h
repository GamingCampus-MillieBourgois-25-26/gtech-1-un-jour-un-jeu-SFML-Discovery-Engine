#pragma once

#include "Core\Component.h"
#include <SquareCollider.h>
#include <RectangleShapeRenderer.h>
#include "Scene.h"

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
};

