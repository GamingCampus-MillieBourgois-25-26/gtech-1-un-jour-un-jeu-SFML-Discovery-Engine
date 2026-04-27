#pragma once
#include "Core/Component.h"
#include <string>
#include "Core/GameObject.h"

class ScoreDisplay : public Component
{
public:
	ScoreDisplay(unsigned int* scor, std::string* n);
	void Update(float _delta_time) override;

	unsigned int* score;
	std::string* nb;
};

