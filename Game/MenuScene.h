#pragma once
#include "MenuScene.h"
#include "RectangleShapeRenderer.h"
#include "ButtonComponent.h"
#include "Core/Scene.h"

class MenuScene final : public Scene {

public:

    MenuScene();    

private:

 
   void CreateButton(const std::string& name, const Maths::Vector2f& pos);

   bool isActive = true;

};