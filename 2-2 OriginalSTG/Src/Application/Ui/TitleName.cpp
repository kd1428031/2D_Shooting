#include "TitleName.h"
#include "Application/ResourceManager.h"

TitleName::TitleName()
{
	Init();
}

void TitleName::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::ktitleName);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
}

void TitleName::UpdateImpl(float dt)
{
	if (m_isExiting)
	{
		m_color.A(m_color.A() - dt);
		m_exitTimer -= dt;
		if (m_exitTimer <= 0)
		{
			m_isAlive = false;
		}
	}
}

void TitleName::Draw()
{
	if (!m_isAlive) return;

	int digits = 14;

	for (int i = 0; i < digits; i++)
	{
		float srcX = kTexFrameWidth * i;

		Math::Rectangle rect{
			(int)srcX, 0, kTexFrameWidth, kTexFrameHeight
		};

		SHADER.m_spriteShader.SetMatrix(CreateMatrix({ (float)(i * (kTexFrameWidth + kTexFrameOffSet)), 0 }));
		SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
	}
}

void TitleName::OnExit()
{
	m_exitTimer = kExitTime;
}
