#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::Init()
{
	m_player = std::make_unique<Player>();
	m_player->Init();
}

void PlayerManager::Update(float dt)
{
	if (!m_player) return;
	m_player->Update(dt);
}

void PlayerManager::Draw()
{
	if (!m_player) return;
	m_player->Draw();
}
