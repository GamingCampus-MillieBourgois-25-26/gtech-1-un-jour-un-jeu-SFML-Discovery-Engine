#include "Match-3/MatchLevel.h"


Match_3::MatchLevel::MatchLevel() : Scene("MatchLevel")
{
	WindowModule* windowModule = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
	AssetsModule* assetModule = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	Texture* texture_TileCow = assetModule->LoadAsset<Texture>("Match_3/cow.png");
	Texture* texture_TileSnake = assetModule->LoadAsset<Texture>("Match_3/snake.png");
	Texture* texture_TileBear = assetModule->LoadAsset<Texture>("Match_3/bear.png");

	textures[0] = texture_TileCow;
	textures[1] = texture_TileSnake;
	textures[2] = texture_TileBear;

	windowModule->SetSize({ 800, 800 });

	GameObject* player = CreateGameObject("Player");
	player->CreateComponent<PlayerMatch>();
	SquareCollider* playerCollider = player->CreateComponent<SquareCollider>();

	GameObject* tileMatch = CreateGameObject("TileMatch");
	TileMatch* tileMatchComponent = tileMatch->CreateComponent<TileMatch>();

	int id = 0;

	for (int i = 0; i < tileMatchComponent->BOARD_SIZE; i++)
	{
		for (int j = 0; j < tileMatchComponent->BOARD_SIZE; j++)
		{
			std::string id_str = std::to_string(id);
			GameObject* tile = CreateGameObject("Tile" + id_str);
			SpriteRenderer* spriteTile = tile->CreateComponent<SpriteRenderer>(textures[rand() % 3]);
		
			tile->CreateComponent<SquareCollider>();
			tile->GetComponent<SquareCollider>()->SetWidth(45.f);
			tile->GetComponent<SquareCollider>()->SetHeight(45.f);
		
			tile->SetPosition({ 45.f * j + 190.f, 45.f * i + 200.f });

			tileMatchComponent->GetTiles()[i][j] = tile;
			id++;
		}
	}
}
