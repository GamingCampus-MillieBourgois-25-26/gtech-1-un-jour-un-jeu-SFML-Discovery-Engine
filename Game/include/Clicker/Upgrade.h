#pragma once
#include "Component.h"

namespace Clicker 
{
	class Upgrade : public Component
	{
	private:
		float upgradeMultiplier = 1.f;
	public:

		void SetDonutTypeUpgrade(int _points);
		void SetGlazingTypeUpgrade(int glazingType);

		float GetUpgradeMultiplier() { return upgradeMultiplier; }
	};
}

