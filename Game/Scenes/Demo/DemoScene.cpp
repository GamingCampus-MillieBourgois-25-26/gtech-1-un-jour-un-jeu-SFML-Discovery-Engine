#include "DemoScene.h"

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene") {
	GameObject* background = CreateGameObject("Background");

	GameObject* player = CreateGameObject("Player");
	player->CreateComponent<BulletHell::Player>(300.f, 550.f);

	GameObject* enemy = CreateGameObject("Enemy");
	enemy->CreateComponent<BulletHell::Enemy>(300.f, 350.f);

	AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
	Texture* texturePlayer = assets_module->LoadAsset<Texture>("playerShip.png");
	Texture* textureBackground = assets_module->LoadAsset<Texture>("wallpaperVoxel.jpg");

	player->CreateComponent<SpriteRenderer>(texturePlayer);
	background->CreateComponent<SpriteRenderer>(textureBackground);
}

GameObject* Demo::DemoScene::CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color) {
    GameObject* game_object = CreateGameObject(_name);
    game_object->SetPosition(Maths::Vector2f(_position, _position));

    SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
    square_collider->SetWidth(20.f);
    square_collider->SetHeight(20.f);

    RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
    shape_renderer->SetColor(_color);
    shape_renderer->SetSize(Maths::Vector2f(200.f, 200.f));

    return game_object;
}

void Demo::DemoScene::ShouldCreateBullet()
{
	if (bulletCount <= 100)
	{
		Logger::Log(ELogLevel::Debug, "Shoot avec succes");

		GameObject* bullet = CreateGameObject("Bullet");
		SquareCollider* square_collider = bullet->CreateComponent<SquareCollider>();
		square_collider->SetWidth(40.f);
		square_collider->SetHeight(20.f);

		RectangleShapeRenderer* shape_renderer = bullet->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetColor(sf::Color::Green);
		shape_renderer->SetSize(Maths::Vector2f(40.f, 20.f));

		bullet->CreateComponent<BulletHell::Bullet>(100.f, 400.f, 400.f);
	}
}
