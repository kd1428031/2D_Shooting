#include "PressStart.h"
#include "Application/ResourceManager.h"

PressStart::PressStart()
{
	Init();
}

void PressStart::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kPressMessage);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
}

void PressStart::UpdateImpl(float dt)
{
	if (m_isExiting)
	{
		m_color.A(m_color.A() - dt);
		m_exitTimer -= dt;
		if (m_exitTimer <= 0)
		{
			m_isAlive = false;
		}
		return;
	}

	if (!m_blink)
	{
		m_color.A(m_color.A() - kBlinkSpeed * 0.02f);
		if (m_color.A() <= kMinBlinkAlpha)m_blink = true;
	}
	else
	{
		m_color.A(m_color.A() + kBlinkSpeed * 0.02f);
		if (m_color.A() >= kMaxBlinkAlpha)m_blink = false;
	}
}

void PressStart::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{ 0,0,kTexWidth,kTexHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void PressStart::OnExit()
{
	m_exitTimer = kExitTime;
}
