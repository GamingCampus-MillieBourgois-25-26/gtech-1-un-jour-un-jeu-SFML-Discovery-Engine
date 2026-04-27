#pragma once
#include "Core/Component.h"
#include <vector>
#include "RectangleShapeRenderer.h"
#include "GameObject.h"



namespace Runner {
	class Level : public Component
	{
	private:
		std::vector<RectangleShapeRenderer*> floor;
	public:
		virtual void Start() override;
		virtual void Update(float deltaTime);
		void CreateFloor(GameObject* fl);
	};

}

