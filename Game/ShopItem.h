#pragma once

#include "GameObject.h"
#include "AnimalData.h"

class SpriteRenderer;

class ShopItem : public GameObject
{
public:
    void Init(const AnimalData& data);

private:
    void OnClick();

    AnimalData m_data;
    bool m_bought = false;

    SpriteRenderer* m_sprite = nullptr;
};