#include "pch.h"
#include "RunnerScene.h"
#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"
#include "Runner/level.h"

Runner::RunnerScene::RunnerScene() : Scene("Scene courir") {
	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	GameObject* flur = CreateGameObject("Flur");
	RectangleShapeRenderer* floor1 = flur->CreateComponent<RectangleShapeRenderer>();
	floor1->SetColor(sf::Color(128, 128, 128));
	floor1->SetSize(Maths::Vector2f(1080, 100));
	flur->SetPosition(Maths::Vector2f(0, 700));

	GameObject* obstacles = CreateGameObject("Obstacles");
	obstacles->CreateComponent<Level>();

	
}