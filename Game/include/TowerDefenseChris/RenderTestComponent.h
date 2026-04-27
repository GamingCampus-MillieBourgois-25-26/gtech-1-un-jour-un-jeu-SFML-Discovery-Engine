#pragma once
#include "Core/Component.h"
#include "SFML/graphics.hpp"

class RendererTestComponent : public Component {
public: 
	sf::RectangleShape rect;
	void Start() override;
	void Render(sf::RenderWindow* window)  override;
	
};