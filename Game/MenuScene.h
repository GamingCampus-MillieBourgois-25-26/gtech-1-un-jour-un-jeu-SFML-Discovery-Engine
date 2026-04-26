#pragma once
#include "Core/Scene.h"
#include "Components/RectangleShapeRenderer.h"
#include "ButtonComponent.h"

enum class ButtonTarget { TowerDefense, BulletHell };

class MenuScene : public Scene {

public:

    MenuScene();

private:

    void CreateButton(const std::string& name,
        const Maths::Vector2f& pos,
        ButtonTarget target);
};