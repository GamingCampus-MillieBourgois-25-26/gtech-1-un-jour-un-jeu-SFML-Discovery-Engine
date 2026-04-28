#include "SelectedTower.h"
#include <iostream>

void SelectedTower::SetSelectedTower(Type* comp)
{
	std::cout << "selection" << std::endl;
	select = comp;
}

Type* SelectedTower::GetSelectedTower()
{
	return select;
}