#include <chrono>
#include <cstdint>
#include <random>


#include "Core/Scene.h"

class Mechant : public Component
{
private:
	int max_hp;
	int hp;
	float ms;
	int spawn_time;
public:
	void Update() {
		Maths::Vector2<float> position = GetOwner()->GetPosition();
		GetOwner()->SetPosition(position);
	}
	Mechant* CreateMechant();
	
};

