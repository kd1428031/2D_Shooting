#include "GrimReaper.h"
#include "Application/ResourceManager.h"
#include "Application/Random/Random.h"
#include "Application/GameObject/Character/Enemy/EnemyManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Gr_Summon.h"

GrimReaper::GrimReaper(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
	m_radius = kRadius;
	m_texFrameWidth = kTexFrameWidth;
	m_texFrameHeight = kTexFrameHeight;
}

void GrimReaper::Init()
{
	m_enemyTag = EnemyTag::Boss;

	m_tex = RESOURCEMANAGER.GetTex(TexName::kGrimReaper_idle);

	m_velocity = kInitVelocity;
	m_hp = kInitHp;
	
	m_score = kScore;
	
	m_flipX *= -1;
	
	m_shotTimer = 0.0f;
	m_shotInterval = kShotInterval;
	m_allShotTimer = 0.0f;

	m_summonTimer = kSummonTimerInterval;
	m_moveTimer = kMoveTimerInterval;

	m_deathFlg = false;
	m_createFlg = false;
	m_moveFlg = false;
	
	m_color.A(0.0f);

	m_bulletOffset = kBulletOffsetX;
	m_bulletSpeed = kBulletSpeed;
	m_bulletScale = kBulletScale;
	m_bulletColor = kBulletColor;
	m_bulletAngleSpeed = kBulletAngleSpeed;

	m_shotFlg = Random::Chance(0.5f);
	m_shotType = (ShotType)Random::Range(0, 3);

	m_shotNWay = 4;
	m_shotAllNWay = 16;

	UpdateMatrix();
}

void GrimReaper::UpdateImpl(float dt)
{
	m_baseAngle += 30.0f * dt;
	if (m_baseAngle >= 360.0f)
	{
		m_baseAngle -= 360.0f;
	}

	float deg = GetAngleDeg(m_pos, PLAYERMANAGER.GetPlayer()->GetPos());
	if (deg > 90 && deg < 270)
	{
		m_flipX = -1;
	}
	else
	{
		m_flipX = 1;
	}

	if (m_moveFlg)
	{
		if (m_pos.x < -50.0f)
		{
			m_velocity.x = 0.0f;
			m_velocity.y = 0.0f;
			m_moveFlg = false;
			m_moveTimer = kMoveTimerInterval;
		}
	}

	UpdateSummon(dt);
	UpdateMove(dt);
	UpdateShot(dt);
	UpdataAnim(dt);
	m_color = { 1,1,1,1 };
}

void GrimReaper::PreUpdate(float dt)
{
	m_state = State::Invincible;

	m_color.A(m_color.A() + dt);
	if (m_color.A() >= 1.0f)
	{
		m_preUpdateFlg = false;
		m_state = State::Alive;
	}
}

void GrimReaper::Shot(float dt)
{
	ShotNWay();
}

void GrimReaper::PreSummon()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kGrimReaper_summon);
	m_animFrame = { 0,0 };
	m_animeState = AnimeState::Summon;

	m_moveTimer = kMoveTimerInterval;
	m_velocity = { 0,0 };
}

void GrimReaper::Summon(float dt)
{
	float angleStep = 360.0f / 8;

	for (int i = 0; i < 8; i++)
	{
		float angle = angleStep * i;
		float rad = DirectX::XMConvertToRadians(angle);

		Math::Vector2 dir =
		{
			cos(rad),
			sin(rad)
		};

		Math::Vector2 spawnPos = m_pos + dir * 100;

		Math::Vector2 offset = spawnPos - m_pos;

		auto* e = ENEMYMANAGER.CreateEnemy(EnemyType::Gr_Summon, spawnPos, true, EnemyBase::ShotType::Aimed);
		auto* gr = static_cast<Gr_Summon*>(e);

		gr->SetOffset(offset);
	}
}

void GrimReaper::UpdateSummon(float dt)
{
	auto summons = ENEMYMANAGER.GetEnemies(EnemyTag::Summoned);

	for (auto* summon : summons)
	{
		auto* gr = static_cast<Gr_Summon*>(summon);
		gr->SetBasePos(m_pos);
	}

	m_summonTimer -= dt;
	if (m_summonTimer <= 0)
	{
		if (summons.size() < kSummonMax / 2 && !m_moveFlg)
		{
			PreSummon();
		}
		m_summonTimer = kSummonTimerInterval;
	}
}

void GrimReaper::UpdateShot(float dt)
{
	if (m_moveFlg || m_movingTimer > 0)return;

		m_shotTimer -= dt;
	if (m_shotTimer <= 0)
	{
		Shot(dt);
		m_shotTimer = m_shotInterval;
	}

	m_allShotTimer -= dt;
	if (m_allShotTimer <= 0)
	{
		ShotAllRange();
		m_allShotTimer = kAllShotTimerInterval;
	}
}

void GrimReaper::UpdateMove(float dt)
{
	if (!m_moveFlg)
	{
		m_moveTimer -= dt;
		if (m_moveTimer <= 0)
		{
			m_moveFlg = true;
			m_moveTimer = kMoveTimerInterval;
			m_movingTimer = kMovingTimerInterval;
			m_targetPos = PLAYERMANAGER.GetPlayer()->GetPos();
		}
	}

	if (m_moveFlg)
	{
		m_movingTimer -= dt;
		if (m_movingTimer > 0)
		{
			float deg = GetAngleDeg(m_pos, m_targetPos);
			float rad = DirectX::XMConvertToRadians(deg);

			Math::Vector2 dir = { cos(rad),sin(rad) };
			m_velocity = dir * kMovingSpeed;
		}
		else if (m_movingTimer <= 0)
		{
			m_moveFlg = false;
			m_velocity = {0, 0};
		}
	}
}

void GrimReaper::UpdataAnim(float dt)
{
	switch (m_animeState)
	{
	case GrimReaper::AnimeState::Idle:

		m_animFrame.x += kAnimSpeed * dt;
		if (m_animFrame.x > kIdleAnimMax)
		{
			m_animFrame.x = 0;
		}
		break;

	case GrimReaper::AnimeState::Summon:

		m_velocity = { 0, 0 };

		m_animFrame.x += kAnimSpeed / 2 * dt;

		if (m_animFrame.x > 1 && m_animFrame.y == 1)
		{
			m_tex = RESOURCEMANAGER.GetTex(TexName::kGrimReaper_idle);
			m_animeState = AnimeState::Idle;

			Summon(dt);
		}

		if (m_animFrame.x > kIdleAnimMax)
		{
			m_animFrame = { 0,1 };
		}
		break;
	}
}

void GrimReaper::OnHit()
{
	//m_tex = RESOURCEMANAGER.GetTex(TexName::kGrimReaper_hit);
	//m_animFrame.x = 1;
	m_color = { 1,0,0,1 };
}

void GrimReaper::PreDeath()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kGrimReaper_death);
	m_animFrame.x = 0;
	m_animFrame.y = 0;
}

void GrimReaper::Death(float dt)
{
	m_animFrame.x += 15 * dt;

	if (m_deathFlg && m_animFrame.y == 1 && m_animFrame.x > 10)
	{
		m_state = State::Dead;
	}

	if (!m_deathFlg)
	{
		if (m_animFrame.x > 10)
		{
			m_animFrame.x = 0;
			m_animFrame.y = 1;
			m_deathFlg = true;
		}
	}
}
