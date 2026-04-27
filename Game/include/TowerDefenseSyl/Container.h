#pragma once
#include "Core/Component.h"
#include "Components/RectangleShapeRenderer.h"
#include "TowerDefenseSyl/SelectedTower.h"

class Container : public Component
{
public:
	Container(RectangleShapeRenderer* shap, SelectedTower* select);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	bool empty = true;
	RectangleShapeRenderer* shape;
	SelectedTower* selector;
	float offset = 15.f;
};

