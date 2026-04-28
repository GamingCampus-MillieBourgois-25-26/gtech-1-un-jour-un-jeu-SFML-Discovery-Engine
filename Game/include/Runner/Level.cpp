#include "pch.h"
#include "Level.h"
#include "Core/Scene.h"

void Runner::Level::Start() 
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
}


void Runner::Level::Update(float deltaTime)
{
	for (GameObject* obs : m_obstacles)
	{
		Maths::Vector2f pos = obs->GetPosition();
		obs->SetPosition(Maths::Vector2f(pos.x - 200.f * deltaTime, pos.y));
	}

	if (m_cooldownTimer > 0.f)
	{
		m_cooldownTimer -= deltaTime;
	}
	else
	{
		float randomY = (rand() % 4 == 0) ? 500.f : 672.f;

		int count = 1 + rand() % 3;
		for (int i = 0; i < count; i++)
		{
			CreateObstacle1(GetOwner()->GetScene(), randomY, i);
		}

		m_cooldownTimer = 2.f + static_cast<float>(rand() % 4);
	}
}

void Runner::Level::CreateObstacle1(Scene* scene, float spawnY, int index)
{
	AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	if (!assets) return;

	Texture* obstacle1_texture = assets->LoadAsset<Texture>("planet00.png");
	if (!obstacle1_texture) return;

	GameObject* obstacle1 = scene->CreateGameObject("obstacle1");
	obstacle1->SetScale(Maths::Vector2f(0.1, 0.1));
	obstacle1->SetPosition(Maths::Vector2f(1100.f + index * 64.f, spawnY));
	SpriteRenderer* render = obstacle1->CreateComponent<SpriteRenderer>(obstacle1_texture);
	obstacle1->CreateComponent<SquareCollider>(render);

	m_obstacles.push_back(obstacle1);
}