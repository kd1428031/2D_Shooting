#pragma once
#include "Player.h"

class PlayerManager
{
public:

	~PlayerManager() = default;

	static PlayerManager& GetInstance()
	{
		static PlayerManager instance;
		return instance;
	}

	void Init();
	void Update(float dt);
	void Draw();

	//void CreatePlayer(Math::Vector2 pos, float scale = 1.0f);

	Player* GetPlayer() const { return m_player.get(); }

private:

	PlayerManager() = default;
	std::unique_ptr<Player>m_player;

};
#define PLAYERMANAGER PlayerManager::GetInstance()