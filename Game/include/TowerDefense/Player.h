#pragma once
#include "Component.h"
#include "InputModule.h"

namespace TowerDefense 
{
	class Player : public Component 
	{
	private:
		int coin;
	public:
		Player(int _coin);

		void Update(float _delta_time) override;

		int getCoin() {
			return coin;
		}
	};
}

