#include "Bat.h"
#include "Application/ResourceManager.h"
#include "Application/Random/Random.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

Bat::Bat(Math::Vector2 pos, float scale)
	: EnemyBase(pos, scale)
{
	m_radius = kRadius;
	m_texFrameWidth = kTexFrameWidth;
	m_texFrameHeight = kTexFrameHeight;
}

void Bat::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kBat);

	if (Random::Chance(0.5))
	{
		float deg = GetAngleDeg(m_pos, PLAYERMANAGER.GetPlayer()->GetPos());
		float rad = DirectX::XMConvertToRadians(deg);

		Math::Vector2 dir = { cos(rad),sin(rad) };

		Math::Vector2 velocity = dir * -kInitVelocity * Random::Range(0.8f, 2.0f);
		m_velocity = velocity;
	}
	else
	{
		m_velocity = kInitVelocity * Random::Range(0.8f, 2.0f);
	}

	m_hp = kInitHp;
	m_score = kScore;
	m_scale = kInitScale;
	m_flipX *= -1;
	m_animFrame.y = 1;
	m_shotTimer = 0.0f;

	m_bulletOffset = kBulletOffsetX;
	m_bulletSpeed = kBulletSpeed;
	m_bulletScale = kBulletScale;
	m_bulletColor = kBulletColor;
	m_bulletAngleSpeed = kBulletAngleSpeed;

	m_shotFlg = Random::Chance(0.5f);
	m_shotType = (ShotType)Random::Range(0, 3);
}

void Bat::UpdateImpl(float dt)
{
	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kIdleAnimMax)
	{
		m_animFrame.x = 0;
		m_animFrame.y = 1;
	}
}

void Bat::OnHit()
{
	m_animFrame.y = 0;
	m_animFrame.x = 1;
}

void Bat::PreDeath()
{
	m_animFrame.y = 2;
	m_animFrame.x = 0;
}

void Bat::Death(float dt)
{
	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kDeathAnimMax)
	{
		m_state = State::Dead;
	}
}
