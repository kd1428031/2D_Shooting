#include "LightningText.h"
#include "Application/ResourceManager.h"

LightningText::LightningText(Math::Vector2 pos, float scale)
	:EffectBase(pos, scale)
{
	Init();
}

void LightningText::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kLightningText);
	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
	m_timer = 0.0f;

	UpdateMatrix();
}

void LightningText::Draw()
{
	if (!m_isAlive)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{ 0,0,kTexWidth,kTexHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void LightningText::UpdateImpl(float dt)
{
	m_timer++;

	if (m_timer <= 10)
	{
		m_color.A(m_color.A() + 0.1f);
		if (m_color.A() >= 1.0f)m_color.A(1.0f);
	}
	else if (m_timer > 30)
	{
		m_color.A(m_color.A() - 0.075f);
		if (m_color.A() <= 0)
		{
			m_isAlive = false;
		}
	}
}
