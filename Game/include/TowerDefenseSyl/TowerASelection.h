#pragma once
#include "Core/Component.h"
#include "TowerDefenseSyl/SelectedTower.h"
#include "Components/RectangleShapeRenderer.h"
#include "Core/GameObject.h"

class TowerASelection : public Component
{
public:
	TowerASelection(RectangleShapeRenderer* shap, SelectedTower* select);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	RectangleShapeRenderer* shape;
	SelectedTower* selector = nullptr;
	char type = 'A';
};

