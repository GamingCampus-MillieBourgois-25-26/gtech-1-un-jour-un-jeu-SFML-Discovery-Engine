#pragma once

#include "Core/Scene.h"

class GameObject;
class TextRenderer;

class Match3UI
{
public:
    void Init(Scene* scene);
    void Update(int score, float timer, bool finished);

private:
    GameObject* m_scoreObject = nullptr;
    GameObject* m_timerObject = nullptr;
    GameObject* m_endObject = nullptr;

    TextRenderer* m_scoreText = nullptr;
    TextRenderer* m_timerText = nullptr;
    TextRenderer* m_endText = nullptr;
};