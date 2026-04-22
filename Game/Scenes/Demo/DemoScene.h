#pragma once

#include "Core/Scene.h"
#include "Demo/Player.h"
#include "Demo/Enemy.h"

namespace Demo
{
    class DemoScene final : public Scene
    {
	private:
		int bulletCount = 0;
    public:
        DemoScene();

        GameObject* CreateDummyGameObject(const std::string& _name, float _position, sf::Color _color);

        void ShouldCreateBullet();
    };
}

