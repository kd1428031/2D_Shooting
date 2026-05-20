#include "HealthPotion.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

HealthPotion::HealthPotion(Math::Vector2 pos, float scale)
	:ItemBase(pos, scale)
{
	m_radius = kRadius;
	m_texFrameWidth = kTexFrameWidth;
	m_texFrameHeight = kTexFrameHeight;
}

void HealthPotion::Init()
{
}

void HealthPotion::UpdateImpl(float dt)
{
}

void HealthPotion::OnHit(Player* player)
{
	player->Heal(kHealValue);
	Destroy();
}
