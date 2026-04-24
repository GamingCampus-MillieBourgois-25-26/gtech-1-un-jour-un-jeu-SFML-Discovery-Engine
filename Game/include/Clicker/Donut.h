#pragma once
#include "Scene.h"
#include "Component.h"
#include <InputModule.h>
#include <AssetsModule.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>

#include <Clicker/Upgrade.h>

namespace Clicker {
	class Donut : public Component
	{
	private:
		bool isClicked = false;
	public:
		void Update(float _delta_time) override;
		bool& GetIsClicked();
		void ToggleIsClicked();
	};
}
