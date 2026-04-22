#include "EnnemyA.h"
#include "SmallBullet.h"
#include "Assets/Texture.h"
#include "Core/GameObject.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"

void EnnemyA::Update(const float _delta_time)
{
	timer += _delta_time;
	if (timer >= 0.2f)
	{
		timer = 0.f;
		GameObject* bullet = CreateGameObject("bullet");
		bullet->SetPosition({ 300.f, 100.f });
		bullet->CreateComponent<SmallBullet>();
		AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
		Texture* texture = assets_module->LoadAsset<Texture>("Sylvain/BulletHell/laserBlue.png");

		bullet->CreateComponent<SpriteRenderer>(texture);
	}
}