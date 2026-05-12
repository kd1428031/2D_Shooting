#pragma once
#include "Player.h"
#include "Raven.h"

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
	void DrawUi();

	void CreateRaven();

	void AddDestroyCnt() { m_destroyCnt++; }

	Player* GetPlayer() const { return m_player.get(); }
	Raven* GetRaven() const { return m_raven.get(); }
	int GetDestroyCnt() const { return m_destroyCnt; }

private:

	PlayerManager() = default;
	std::unique_ptr<Player>m_player;
	std::unique_ptr<Raven>m_raven;

	int m_destroyCnt;

};
#define PLAYERMANAGER PlayerManager::GetInstance()