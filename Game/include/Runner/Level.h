#pragma once
#include "Core/Component.h"
#include <vector>
#include "RectangleShapeRenderer.h"
#include "GameObject.h"
#include "Asset.h"
#include "Texture.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"




namespace Runner {
	class Level : public Component
	{
	private:
		float x = 1100;
		float m_cooldownTimer = 0.f;
		const float COOLDOWN_DURATION = 10.f;
		std::vector<GameObject*> m_obstacles;
	public:
		virtual void Start() override;
		virtual void Update(float deltaTime);
		void CreateObstacle1(Scene* scene, float spawnY = 500.f, int index = 0);
	};

}

