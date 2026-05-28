#include "MpMax.h"
#include "Application/ResourceManager.h"

MpMax::MpMax(Math::Vector2 pos, float scale)
	: EffectBase(pos, scale)
{
	Init();
}

void MpMax::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kMpMax);
	m_color = kInitColor;

	m_animFrame = {};

	UpdateMatrix();
}

void MpMax::DrawFront()
{
	if (!m_isAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{
		kTexFrameWidth * (int)m_animFrame.x,
		kTexFrameHeight * (int)m_animFrame.y, kTexFrameWidth, kTexFrameHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void MpMax::UpdateImpl(float dt)
{
	if (!m_isAlive)return;

	m_animFrame.x += kAnimSpeed * dt;
	if (m_animFrame.x > kAnimMaxX)
	{
		m_isAlive = false;
	}
}
