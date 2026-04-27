#include "pch.h"
#include "Level.h"
#include "Core/Scene.h"

void Runner::Level::Start() 
{
	Scene* scene = GetOwner()->GetScene();
}

void Runner::Level::Update(float deltaTime) {
	
}

void Runner::Level::CreateFloor(GameObject* fl)
{
	RectangleShapeRenderer* floor1 = fl->CreateComponent<RectangleShapeRenderer>();
	floor1->SetColor(sf::Color(128, 128, 128));
	floor1->SetSize(Maths::Vector2f(500, 100));
	RectangleShapeRenderer* floor2 = fl->CreateComponent<RectangleShapeRenderer>();
	floor2->SetColor(sf::Color(128, 128, 128));
	floor2->SetSize(Maths::Vector2f(500, 100));
	RectangleShapeRenderer* floor3 = fl->CreateComponent<RectangleShapeRenderer>();
	floor3->SetColor(sf::Color(128, 128, 128));
	floor3->SetSize(Maths::Vector2f(500, 100));
}

