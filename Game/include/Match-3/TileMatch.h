#pragma once
#include "Component.h"

namespace Match_3 
{
	class TileMatch : public Component
	{
	public:
		static const int BOARD_SIZE = 2;

		void Start() override;
		void Update(float deltaTime) override;
		void Render(sf::RenderWindow* window) override;

		auto& GetTiles() { return Tiles; }
	private:
		GameObject* Tiles[BOARD_SIZE][BOARD_SIZE];
	};
}


