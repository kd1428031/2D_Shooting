#include "Gr_Summon.h"
#include "Application/ResourceManager.h"
#include "Application/Random/Random.h"

Gr_Summon::Gr_Summon(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
	m_radius = kRadius;
	m_texFrameWidth = kTexFrameWidth;
	m_texFrameHeight = kTexFrameHeight;
}

void Gr_Summon::Init()
{
	m_enemyTag = EnemyTag::Summoned;

	m_tex = RESOURCEMANAGER.GetTex(TexName::kGr_SummonAppear);
	m_velocity = kInitVelocity;
	m_hp = kInitHp;
	m_score = kScore;
	m_scale = kInitScale;
	m_flipX *= -1;
	m_animFrame.y = 1;
	m_shotTimer = 0.0f;
	m_shotInterval = kShotInterval;

	m_bulletOffset = kBulletOffsetX;
	m_bulletSpeed = kBulletSpeed;
	m_bulletScale = kBulletScale;
	m_bulletColor = kBulletColor;
	m_bulletAngleSpeed = kBulletAngleSpeed;

	m_shotFlg = true;
	m_shotType = ShotType::Aimed;

	m_preAnimFlg = true;
	m_deathFlg = false;

	m_basePos = {};
	m_deg = 0.0f;

	UpdateMatrix();
}

void Gr_Summon::UpdateImpl(float dt)
{
	m_deg += 90.0f * dt;
	if (m_deg >= 360.0f)m_deg -= 360.0f;

	float rad = DirectX::XMConvertToRadians(m_deg);

	float cosA = cos(rad);
	float sinA = sin(rad);

	// 回転行列でoffset回す
	Math::Vector2 rotated;
	rotated.x = m_offset.x * cosA - m_offset.y * sinA;
	rotated.y = m_offset.x * sinA + m_offset.y * cosA;

	// 親に追従
	m_pos = m_basePos + rotated;

	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kIdleAnimMax)
	{
		m_animFrame.x = 0;
	}
}

void Gr_Summon::OnHit()
{
	m_animFrame.y = 0;
}

void Gr_Summon::PreUpdate(float dt)
{
	m_state = State::Invincible;

	m_animFrame.x += kAnimSpeed * 2 * dt;

	if (!m_preAnimFlg && m_animFrame.y >= kDeathAnimMaxY && m_animFrame.x > kDeathAnimMaxX - 1)
	{
		m_tex = RESOURCEMANAGER.GetTex(TexName::kGr_Summon_idle);
		m_preUpdateFlg = false;
		m_state = State::Alive;
	}

	if (m_preAnimFlg)
	{
		if (m_animFrame.x > kDeathAnimMaxX)
		{
			m_animFrame.x = 0;
			m_animFrame.y = 1;
			m_preAnimFlg = false;
		}
	}
	UpdateMatrix();
}

void Gr_Summon::PreDeath()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kGr_Summon_death);

	m_animFrame.y = 0;
	m_animFrame.x = 0;
}

void Gr_Summon::Death(float dt)
{
	m_animFrame.x += kAnimSpeed * 3 * dt;

	if (m_deathFlg && m_animFrame.y >= kDeathAnimMaxY && m_animFrame.x > kDeathAnimMaxX - 1)
	{
		m_state = State::Dead;
	}

	if (!m_deathFlg)
	{
		if (m_animFrame.x > kDeathAnimMaxX)
		{
			m_animFrame.x = 0;
			m_animFrame.y = 1;
			m_deathFlg = true;
		}
	}
}
