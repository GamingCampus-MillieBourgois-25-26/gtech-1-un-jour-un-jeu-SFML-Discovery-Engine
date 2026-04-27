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
	flur->CreateComponent<Level>();
}