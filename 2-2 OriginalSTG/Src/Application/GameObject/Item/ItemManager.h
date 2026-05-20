#pragma once
#include "ItemBase.h"

class ItemManager
{
public:

	enum class ItemType
	{
		Hp,
		Mp,
		End
	};

	~ItemManager() = default;

	static ItemManager& GetInstance()
	{
		static ItemManager instance;
		return instance;
	}

	void Init();
	void Update(float dt);
	void Draw();

	int GetItemNum() { return (int)m_item.size(); }

	void RandomCreateItem(Math::Vector2 pos, float scale = 1.0f);
	void CreateItem(ItemType type, Math::Vector2 pos,float scale = 1.0f);

	void AllDestroy();

	const std::vector < std::unique_ptr<ItemBase>>& GetItem() const { return m_item; }

private:

	ItemManager() = default;
	std::vector<std::unique_ptr<ItemBase>>m_item;

};
#define ITEMMANAGER ItemManager::GetInstance()