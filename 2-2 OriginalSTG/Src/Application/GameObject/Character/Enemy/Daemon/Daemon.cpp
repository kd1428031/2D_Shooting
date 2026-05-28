#include "Daemon.h"
#include "Application/ResourceManager.h"
#include "Application/Audio/AudioManager.h"
#include "Application/Random/Random.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

Daemon::Daemon(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
	m_radius = kRadius;
	m_texFrameWidth = kTexFrameWidth;
	m_texFrameHeight = kTexFrameHeight;
}

void Daemon::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kDaemon_idle);

	m_velocity = kInitVelocity;
	m_hp = kInitHp;
	m_score = kScore;
	m_shotTimer = 0.0f;

	m_bulletOffset = kBulletOffsetX;
	m_bulletSpeed = kBulletSpeed;
	m_bulletScale = kBulletScale;
	m_bulletColor = BulletColor::Red;
	m_bulletAngleSpeed = kBulletAngleSpeed;

	m_shotType = (ShotType)Random::Range(0, 3);
}

void Daemon::UpdateImpl(float dt)
{
	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kIdleAnimMax)
	{
		m_animFrame.x = 0;
		m_tex = RESOURCEMANAGER.GetTex(TexName::kDaemon_idle);
	}
}

void Daemon::OnHit()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kDaemon_hit);
	m_animFrame.x = 1;
}

void Daemon::PreDeath()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kDaemon_death);
	m_animFrame.x = 0;

	AUDIOM.PlaySeNumLimit(SoundName::kEnemyDestroy);
}

void Daemon::Death(float dt)
{
	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kDeathAnimMax)
	{
		m_state = State::Dead;
	}
}
