#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::Init()
{
	m_player = std::make_unique<Player>();
	m_player->Init();
}

void PlayerManager::Update(float dt)
{
	m_player->Update(dt);
}

void PlayerManager::Draw()
{
	m_player->Draw();
}
