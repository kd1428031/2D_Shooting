#include "MagicCircle.h"
#include "Application/ResourceManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

MagicCircle::MagicCircle(Math::Vector2 pos, float scale)
	: EffectBase(pos, scale), m_onExitFlg(false)
{
	Init();
}

void MagicCircle::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kMagicCircle_summon);
	m_color = kInitColor;
	m_angle = kInitAngle;

	m_animFrame = { 0,0 };

	m_upperFlg = true;

	UpdateMatrix();
}

void MagicCircle::DrawBack()
{
	if (!m_isAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{
		kTexFrameWidth * (int)m_animFrame.x,
		0, kTexFrameWidth, kTexFrameHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void MagicCircle::UpdateImpl(float dt)
{
	if (!m_isAlive)return;
	if (!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		Kill();
	}

	m_targetPos = PLAYERMANAGER.GetPlayer()->GetPos();
	m_pos = m_targetPos;

	if (!m_onExitFlg)
	{
		if (m_upperFlg)
		{
			m_animFrame.x += kAnimSpeed * dt;
			if (m_animFrame.x > kAnimMaxX)
			{
				m_animFrame.x = 0;
				m_upperFlg = false;
				m_tex = RESOURCEMANAGER.GetTex(TexName::kMagicCircle_idle);
			}
		}
		else
		{
			m_animFrame.x += kAnimSpeed * dt;
			if (m_animFrame.x > kAnimMaxX)
			{
				m_animFrame.x = 0;
			}
		}
	}

	if (m_onExitFlg)
	{
		m_animFrame.x -= kAnimSpeed * dt;
		if (m_animFrame.x < 0)
		{
			m_animFrame.x = 0;
			m_isAlive = false;
		}
	}
}

void MagicCircle::UpdateMatrix()
{
	m_mat = CreateMatrix(m_pos, { m_scale, m_scale }, m_angle);
}

void MagicCircle::OnExit()
{
	m_onExitFlg = true;
	m_tex = RESOURCEMANAGER.GetTex(TexName::kMagicCircle_summon);
}
