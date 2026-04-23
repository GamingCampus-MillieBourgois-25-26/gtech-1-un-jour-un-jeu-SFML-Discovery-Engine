#include "Spawner.h"
#include "TowerDefenseSyl/EnemyAComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include <iostream>

Spawner::Spawner(std::vector<Maths::Vector2f> inPath)
{
	path = inPath;
}

void Spawner::Update(float _delta_time)
{
	if (wave == 0 && delay >= 0.f)
		delay -= _delta_time;
	else if (wave == 1)
	{
		Wave1(_delta_time);
	}
	else
	{
		delay = 1.f;
		wave++;
	}
}

void Spawner::Wave1(float _delta_time)
{
	timer += _delta_time;
	if (timer >= 1.f)
	{
		timer = 0.f;
		count++;
		std::cout << "spawn" << std::endl;
		GameObject* enemy = GetOwner()->GetScene()->CreateGameObject("enemy");
		enemy->CreateComponent<EnemyAComponent>(path);
		enemy->SetPosition(spawnPoint);
		RectangleShapeRenderer* shape_renderer = enemy->CreateComponent<RectangleShapeRenderer>();
		if (count == 10)
		{
			timer = 0.f;
			count = 0;
			wave++;
		}
	}
}