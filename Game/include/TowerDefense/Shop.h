#pragma once
#include "Component.h"
#include "GameObject.h"
#include <InputModule.h>
#include <TowerDefense/Player.h>
#include <SFML/Graphics/Rect.hpp>

namespace TowerDefense 
{
	class Shop : public Component
	{
	private:
		sf::Vector2f position;
		sf::FloatRect bounds;
	public:
		Shop(sf::Vector2f _position);

		void Start() override;
		void Update(float _delta_time) override;
	};
}

