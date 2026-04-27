#pragma once
#include "Core/Scene.h"
#include <vector>

class Shapes : public Component
{
public:
	
	Shapes* Square();

	void Update(const float _delta_time) override;

private:
	std::vector<Shapes*> shape_list;
	float speed = 100.0f;
};

