#pragma once
#include "Component.h"
#include "Scene.h"
#include <InputModule.h>
#include <AssetsModule.h>
#include <Texture.h>
#include <SpriteRenderer.h>
#include <Clicker/Upgrade.h>

namespace Clicker {
	class ShopUpgrade : public Component
	{
	private:
		AssetsModule* assets_module;
		std::string typeUpgrade;

		bool leftClickPressed;
		int mousePositionX;
		int mousePositionY;

	public:
		ShopUpgrade(std::string _typeUpgrade);

		void Start() override;
		void Update(float _delta_time) override;

		void BuyUpgrade(std::string _typeUpgrade);
	};
}


