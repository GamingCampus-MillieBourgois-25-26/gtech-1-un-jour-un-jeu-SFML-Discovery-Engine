#pragma once

#include "SPlayer.h"
#include "EnnemyA.h"
#include "Assets/Texture.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"

class BulletHellSyl final : public Scene
{
public:
	BulletHellSyl() : Scene("BulletHellSyl")
	{
		GameObject* player = CreateDummyGameObject("Player", { 250.f, 400.f }, sf::Color::Red);
		player->CreateComponent<SPlayer>();

		GameObject* enemy = CreateDummyGameObject("Enemy", { 100.f, 250.f }, sf::Color::Blue);
		enemy->CreateComponent<EnnemyA>();

		//GameObject* enemy2 = CreateDummyGameObject("Enemy2", { 0.f, 50.f }, sf::Color::Yellow);

		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* texture = assets_module->LoadAsset<Texture>("logo.png");

		player->CreateComponent<SpriteRenderer>(texture);
	}

	GameObject* CreateDummyGameObject(const std::string& _name, const Maths::Vector2f _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(20.f);
		square_collider->SetHeight(20.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(_color);
		shape_renderer->SetSize(Maths::Vector2f(100.f, 100.f));

		return game_object;
	}
};

