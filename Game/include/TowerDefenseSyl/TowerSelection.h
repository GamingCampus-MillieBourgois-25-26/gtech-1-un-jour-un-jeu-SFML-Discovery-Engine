#pragma once
#include "Core/Component.h"
#include "TowerDefenseSyl/SelectedTower.h"
#include "Components/RectangleShapeRenderer.h"
#include "Core/GameObject.h"

enum class Type
{
	A,
	B
};

class TowerSelection : public Component
{
public:
	TowerSelection(RectangleShapeRenderer* shap, SelectedTower* select, Type TowerType);
	void Update(float _delta_time) override;
	bool IsUnderCursor();

	RectangleShapeRenderer* shape;
	SelectedTower* selector = nullptr;
	Type type;
	int cost = 5;
};

