#pragma once
#include "Scene.h"
#include <AssetsModule.h>
#include <WindowModule.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include <RectangleShapeRenderer.h>

#include <Match-3/PlayerMatch.h>
#include <Match-3/TileMatch.h>

namespace Match_3
{
	class MatchLevel : public Scene
	{
	private:
		const float TEXTURE_SIZE = 45.f;
		Texture* textures[3];

	public:
		MatchLevel();
	};
}


