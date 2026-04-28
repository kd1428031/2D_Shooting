#include "WarningCutIn.h"
#include "Application/ResourceManager.h"

WarningCutIn::WarningCutIn()
{
	Init();
}

void WarningCutIn::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kWarning);
	m_pos = kInitPos;
	m_velocity = kInitVelocity;
	m_scale = kInitScale;
	m_color = kInitColor;
	m_angle = kInitAngle;
}

void WarningCutIn::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{ 0,0,kTexWidth,kTexHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void WarningCutIn::UpdateImpl(float dt)
{
	m_pos += m_velocity * dt;
}
