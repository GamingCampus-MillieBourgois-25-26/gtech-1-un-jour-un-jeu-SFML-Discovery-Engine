#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Components/TextRenderer.h"

class Star : public Component
{
public:
	Star(GameObject* obj);
	Star(GameObject* obj, Star* prev);
	void Update(const float _delta_time) override;
	void SetNext(Star* nextStar);

	Star* next;
	GameObject* player;
};

