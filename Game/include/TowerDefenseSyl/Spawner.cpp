#include "Spawner.h"
#include "TowerDefenseSyl/EnemyComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include <iostream>

Spawner::Spawner(std::vector<Maths::Vector2f> inPath, HQComponent* QGComp, int* argent)
{
	path = inPath;
	QG = QGComp;
	gold = argent;
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
	if (timer >= 0.3f)
	{
		timer = 0.f;
		count++;
		//std::cout << "spawn" << std::endl;
		GameObject* enemy = GetOwner()->GetScene()->CreateGameObject("enemy");
		enemy->CreateComponent<EnemyComponent>(path, QG, gold);
		enemy->SetPosition(spawnPoint);
		RectangleShapeRenderer* shape_renderer = enemy->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(sf::Color::Yellow);
		shape_renderer->SetSize(Maths::Vector2f(20.f, 20.f));
		if (count == 20)
		{
			timer = 0.f;
			count = 0;
			wave++;
		}
	}
}