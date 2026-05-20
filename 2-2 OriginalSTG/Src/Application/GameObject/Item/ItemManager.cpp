#include "ItemManager.h"
#include "HealthPotion/HealthPotion.h"
#include "ManaPotion/ManaPotion.h"
#include "Application/Random/Random.h"

void ItemManager::Init()
{
	m_item.clear();
}

void ItemManager::Update(float dt)
{
    for (int i = m_item.size() - 1; i >= 0; --i)
    {
        m_item[i]->Update(dt);

        // 死んでたら削除
        if (!m_item[i]->IsAlive())
        {
            m_item.erase(m_item.begin() + i);
        }
    }
}

void ItemManager::Draw()
{
    for (auto& item : m_item)
    {
        item->Draw();
    }
}

void ItemManager::RandomCreateItem(Math::Vector2 pos, float scale = 1.0f)
{
    ItemType type = (ItemType)Random::Range(0, (int)ItemType::End);
    {
        CreateItem(type, pos, scale);
    }
}

void ItemManager::CreateItem(ItemType type, Math::Vector2 pos, float scale)
{
    std::unique_ptr<ItemBase> item;

    switch (type)
    {
    case ItemType::Hp:
        item = std::make_unique<HealthPotion>(pos, scale);
        break;

    case ItemType::Mp:
        //item = std::make_unique<ManaPotion>(pos, scale);
        break;
    }

    if (item)
    {
        m_item.emplace_back(std::move(item));
    }
}

void ItemManager::AllDestroy()
{
    for (auto& item : m_item)
    {
        item->Destroy();
    }
}
