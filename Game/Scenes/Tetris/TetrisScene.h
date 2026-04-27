#pragma once
#include "Core/Scene.h"

namespace Tetris {
	class TetrisScene : public Scene
	{
	public:
		TetrisScene();

		void CreateLvl();
		
	private:
		static constexpr int COLS = 10;
		static constexpr int ROWS = 20;
		static constexpr float CELL_SIZE = 40.f;

		int grid[ROWS][COLS] = {};
	};
}