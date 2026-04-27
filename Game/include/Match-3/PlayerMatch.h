#pragma once
#include "Component.h"
#include <InputModule.h>
#include <SquareCollider.h>
#include <Match-3/TileMatch.h>
#include "Scene.h"

class PlayerMatch : public Component
{
private:
	SquareCollider* ownerCollider = nullptr;
	Scene* sceneOwner = nullptr;
	int id = 0;
	const int BOARD_SIZE = 2;

	bool isDragging = false;
	Maths::Vector2i clickPosition;
	SquareCollider* selectedTile = nullptr;

	int index_I = 0;
	int index_J = 0;

public:
	void Start() override;
	void Update(float deltaTime) override;

	SquareCollider* ReturnTileName(int id);
	void swapPosition(int i, int j);
};

