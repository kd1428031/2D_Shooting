#include "PlayerManager.h"

void PlayerManager::Init()
{
	m_player = std::make_unique<Player>();
	
	m_player->Init();

	m_raven = std::make_unique<Raven>();
	m_raven->Init();

	m_destroyCnt = 0;
}

void PlayerManager::Update(float dt)
{
	if (m_player)
	{
		m_player->Update(dt);
	}

	if (m_raven)
	{
		m_raven->Update(dt);
	}
}

void PlayerManager::Draw()
{
	if (m_player)
	{
		m_player->Draw();
	}

	if (m_raven)
	{
		m_raven->Draw();
	}
}

void PlayerManager::DrawUi()
{
	if (m_player)
	{
		m_player->DrawUi();
	}
}

void PlayerManager::CreateRaven()
{
	m_raven = std::make_unique<Raven>();
	m_raven->Init();
}
