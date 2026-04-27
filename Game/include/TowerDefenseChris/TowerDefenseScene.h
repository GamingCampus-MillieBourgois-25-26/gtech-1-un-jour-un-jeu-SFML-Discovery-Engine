#pragma once 
#include "Core/Scene.h"

namespace TowerDefense
{
	class TowerDefenseScene : public Scene

	{
	public:
		TowerDefenseScene();

	private:
		int enemiesKilled = 0;
		int baseHP = 3;
	};
};
