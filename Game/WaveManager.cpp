#include "WaveManager.h"

#include "Core/GameObject.h"
#include "Core/Module.h"



Maths::Vector2f WaveManager::findPlayer(GameObject* player)
{
	Maths::Vector2f Player_pos = player->GetPosition();
	Maths::Vector2f Mechant_pos = GetOwner()->GetPosition();
	Maths::Vector2f direction = Maths::Vector2f((Player_pos.x - Mechant_pos.x), (Player_pos.y - Mechant_pos.y));
	float distance = direction.Magnitude();
	
	direction = direction.Normalize();
	return direction;
}

void WaveManager::SpawMechant()
{
}

void WaveManager::CreateWave()
{

}
