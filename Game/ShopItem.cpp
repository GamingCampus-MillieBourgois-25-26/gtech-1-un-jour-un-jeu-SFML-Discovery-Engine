#include "ShopItem.h"
#include "SpriteRenderer.h"
#include "GameManager.h"
#include "Engine.h"

void ShopItem::Init(const AnimalData& data)
{
    m_data = data;

}

void ShopItem::OnClick()
{
    if (m_bought)
        return;

    if (GameManager::Get().SpendPoints(m_data.price))
    {
        m_bought = true;
        GameManager::Get().AddClickBonus(m_data.clickBonus);

        // option : griser le sprite
    }
}