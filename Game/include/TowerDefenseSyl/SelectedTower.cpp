#include "SelectedTower.h"
#include <iostream>

void SelectedTower::SetSelectedTower(char* comp)
{
	std::cout << "selection" << std::endl;
	select = comp;
}

char* SelectedTower::GetSelectedTower()
{
	return select;
}