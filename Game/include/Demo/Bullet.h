#pragma once
#include "Core/Component.h"

namespace Demon {
	class Bullet : public Component {
	public:
		void Update(const float _delta_time) override {
			Maths::Vector2<float> position = GetOwner()->GetPosition();
			GetOwner()->SetPosition(position);
		}

	private:
		float speed = 300.f;
	};
}