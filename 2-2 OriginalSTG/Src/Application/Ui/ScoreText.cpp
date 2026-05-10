#include "ScoreText.h"
#include "Application/ResourceManager.h"

ScoreText::ScoreText()
{
	Init();
}

void ScoreText::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kScore);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
}

void ScoreText::UpdateImpl(float dt)
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
}

void ScoreText::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{ 0,0,kTexWidth,kTexHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void ScoreText::OnExit()
{
	m_exitTimer = kExitTime;
}
