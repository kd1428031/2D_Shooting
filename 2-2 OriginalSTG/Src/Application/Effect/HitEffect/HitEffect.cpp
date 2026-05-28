#include "HitEffect.h"
#include "Application/ResourceManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/TimeManager.h"

HitEffect::HitEffect(Math::Vector2 pos, float scale)
	: EffectBase(pos, scale)
{
	Init();
}

void HitEffect::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kHitEffect);
	m_color = kInitColor;
	m_angle = kInitAngle;

	m_animFrame = {};
	m_timer = 3.0f;

	UpdateMatrix();
}

void HitEffect::DrawFront()
{
	if (!m_isAlive)return;
	if (m_timer > 0)
	{
		D3D.SetBlendState(BlendMode::Add);
		SHADER.m_spriteShader.SetMatrix(m_mat);

		Math::Rectangle rect{
			0,0,
			kTexFrameWidth, kTexFrameHeight };

		SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
		D3D.SetBlendState(BlendMode::Alpha);
	}
}

void HitEffect::UpdateImpl(float dt)
{
	if (!m_isAlive)return;

	m_timer -= dt;
	m_scale *= 1.2f;
	if (m_timer > 0)
	{
		m_color.A(m_color.A() - 0.06f);
		//m_animFrame.x += kAnimSpeed * dt;
		//if (m_animFrame.x > kAnimMaxX)
		if(m_color.A() <= 0.0f)
		{
			m_isAlive = false;
		}
	}

	if(m_timer <= 0.0f)m_isAlive = false;
}
