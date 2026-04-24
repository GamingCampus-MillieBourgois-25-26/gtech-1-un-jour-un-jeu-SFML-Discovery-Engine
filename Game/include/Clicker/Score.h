#pragma once
#include "Component.h"
#include "Scene.h"
#include "Clicker/Donut.h"
#include "Clicker/Upgrade.h"
#include "SFML/Graphics/Font.hpp"
#include <SFML/Graphics/Text.hpp>

namespace Clicker 
{
	class Score : public Component
	{
	private:
		float points = 0;
		Donut* donutComponent = nullptr;
		Upgrade* upgradeComponent = nullptr;
	public:
		Score(float _points);

		void Start() override;
		void Update(float _delta_time) override;

		void AddPoints(float value) { points += value; }
		float GetPoints() { return points; }
	};
}

