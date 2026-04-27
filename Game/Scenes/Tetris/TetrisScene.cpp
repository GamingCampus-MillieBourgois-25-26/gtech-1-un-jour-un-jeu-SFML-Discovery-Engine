#include "TetrisScene.h"
#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"

Tetris::TetrisScene::TetrisScene() : Scene("TetrisScene")
{
	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	CreateLvl();
}

void Tetris::TetrisScene::CreateLvl()
{
	

	for (int row = 0; row < ROWS; row++) {
		for (int cols = 0; cols < COLS; cols++) {
			GameObject* cell = CreateGameObject("Cell");

			RectangleShapeRenderer* rect = cell->CreateComponent<RectangleShapeRenderer>();
			rect->SetSize(Maths::Vector2f(CELL_SIZE - 1.f, CELL_SIZE - 1.f));
			rect->SetColor(sf::Color(50, 50, 50));

			cell->SetPosition(Maths::Vector2f(
				15.f + cols * CELL_SIZE,
				10.f + row * CELL_SIZE
			));
		}
	}
}


