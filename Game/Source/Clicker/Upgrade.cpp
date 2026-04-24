#include "Clicker/Upgrade.h"

void Clicker::Upgrade::SetDonutTypeUpgrade(int donutType)
{
	switch (donutType)
	{
	// brown donut
	case 0:
		upgradeMultiplier += 0.1f;
		break;
	// black donut 
	case 1:
		upgradeMultiplier += 0.3f;
		break;
	default:
		break;
	}
}

void Clicker::Upgrade::SetGlazingTypeUpgrade(int glazingType)
{
	switch (glazingType)
	{
	// pink glazing
	case 0:
		upgradeMultiplier += 0.1f;
		break;

	// brown glazing 
	case 1:
		upgradeMultiplier += 0.2f;
		break;

	// green glazing
	case 2:
		upgradeMultiplier += 0.6f;
		break;

	default:
		break;
	}
}
