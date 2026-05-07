#include "GameStart.h"
#include "Application/ResourceManager.h"
#include "Application/Scene/SceneManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Ui/UiManager.h"

GameStart::GameStart()
{
	Init();
}

void GameStart::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kStart);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
	m_isClicked = false;
	m_blink = false;
}

void GameStart::UpdateImpl(float dt)
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

	POINT mouse = INPUT.GetMousePos();

	if (mouse.x > m_pos.x - (kTexWidth / 6) &&
		mouse.x < m_pos.x + (kTexWidth / 6) &&
		mouse.y > m_pos.y - (kTexHeight / 6) &&
		mouse.y < m_pos.y + (kTexHeight / 6))
	{
		m_scale += (kMaxScale - m_scale) * kScaleChangeSpeed * dt;

		m_color.A(kMaxBlinkAlpha);
		
		if (INPUT.IsTriggerLeftClick())
		{
			m_isClicked = true;
		}
	}
	else
	{
		m_scale += (kInitScale - m_scale) * kScaleChangeSpeed * dt;

		if (!m_blink)
		{
			m_color.A(m_color.A() - kBlinkSpeed * dt);
			if (m_color.A() <= kMinBlinkAlpha)m_blink = true;
		}
		else
		{
			m_color.A(m_color.A() + kBlinkSpeed * dt);
			if (m_color.A() >= kMaxBlinkAlpha)m_blink = false;
		}
	}
}

void GameStart::Draw()
{
	if (!m_isAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Rectangle rect{ 0,0,kTexWidth,kTexHeight };

	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void GameStart::OnExit()
{
	m_exitTimer = kExitTime;
	m_color.A(kMaxBlinkAlpha);
}