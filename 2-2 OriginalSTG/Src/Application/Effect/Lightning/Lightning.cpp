#include "Lightning.h"
#include "Application/ResourceManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/TimeManager.h"

Lightning::Lightning(Math::Vector2 pos, float scale)
	: EffectBase(pos, scale)
{
	Init();
}

void Lightning::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kLightning);
	m_velocity = kInitVelocity;
	m_color = kInitColor;
	m_angle = kInitAngle;

	m_animFrame = {};
	m_timer = 0.0f;

	UpdateMatrix();
}

void Lightning::Draw()
{
	if (!m_isAlive)return;
	if (m_timer > 20)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);

		Math::Rectangle rect{
			kTexFrameWidth * (int)m_animFrame.x,
			kTexFrameHeight * (int)m_animFrame.y, kTexFrameWidth, kTexFrameHeight };

		SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
	}
}

void Lightning::UpdateImpl(float dt)
{
	if (!m_isAlive)return;

	m_timer++;

	if (m_timer > 20)
	{
		m_animFrame.x += kAnimSpeed;
		if (m_animFrame.x > kAnimMaxX)
		{
			m_animFrame.x = 0;
			m_animFrame.y++;
		}
		if (m_animFrame.y > kAnimMaxY)
		{
			m_isAlive = false;
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
		}
	}
}
