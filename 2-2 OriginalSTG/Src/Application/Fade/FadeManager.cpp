#include "FadeManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"
#include "Application/Audio/AudioManager.h"

void FadeManager::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kFade);

	m_color = kBlack;
	m_fadeInFlg = false;
	m_fadeOutFlg = false;
	m_fadeEndFlg = false;
	m_fadeSpeed = 0;
}

void FadeManager::Update(float dt)
{
	if (m_fadeInFlg)
	{
		m_color.A(m_color.A() - (m_fadeSpeed * 0.02f));
		if (m_color.A() <= 0)
		{
			m_fadeInFlg = false;
			m_fadeEndFlg = true;
		}
	}
	else if (m_fadeOutFlg)
	{
		m_color.A(m_color.A() + (m_fadeSpeed * 0.02f));
		if (m_color.A() >= 1)
		{
			m_fadeOutFlg = false;
			m_fadeEndFlg = true;
		}
	}

	else if (m_blinkFlg)
	{
		m_timer -= dt;
		if (m_timer > 0)
		{
			if (!m_blink)
			{
				m_color.A(m_color.A() + (m_fadeSpeed * dt));
				if (m_color.A() >= 1)
				{
					m_blink = true;
					AUDIOM.PlaySe(SoundName::kHeartbeat);
				}
			}
			else if (m_blink)
			{
				m_color.A(m_color.A() - (m_fadeSpeed * dt));
				if (m_color.A() <= 0)
				{
					m_blink = false;
				}
			}
		}
		else
		{
			m_timer = 0;
			if (m_color.A() > 0.0f)
			{
				m_color.A(m_color.A() - (m_fadeSpeed * dt));
			}
			if (m_color.A() <= 0.0f)
			{
				m_color = kBlack;
				m_color.A(0);
				m_blinkFlg = false;
				m_blinkEnd = true;
			}
		}
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(SCENE.GetScreenWidth(), SCENE.GetScreenHeight(), 1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mat = scaleMat * transMat;
}

void FadeManager::Draw()
{
	Math::Rectangle rect = { 0,0,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void FadeManager::FadeIn(float fadeSpeed, Math::Color color)
{
	m_blinkFlg = false;

	m_color = color;
	m_color.A(1.0f);
	m_fadeInFlg = true;
	m_fadeEndFlg = false;
	m_fadeSpeed = fadeSpeed;
}

void FadeManager::FadeOut(float fadeSpeed, Math::Color color)
{
	m_blinkFlg = false;    
	m_blinkEnd = false;    

	m_color = color;
	m_color.A(0.0f);
	m_fadeOutFlg = true;
	m_fadeEndFlg = false;
	m_fadeSpeed = fadeSpeed;
}

bool FadeManager::IsFadeEnd()
{
	return m_fadeEndFlg;
}

bool FadeManager::IsFading()
{
	if (m_fadeInFlg || m_fadeOutFlg)
	{
		return true;
	}
	return false;
}

void FadeManager::Blink(float time, float speed, Math::Color color)
{
	m_fadeInFlg = false;
	m_fadeOutFlg = false;

	m_blinkFlg = true;
	m_blink = false;
	m_blinkEnd = false;
	m_fadeSpeed = speed;
	m_color = color;
	m_color.A(0.0f);
	m_timer = time;
}

bool FadeManager::IsBlinkEnd()
{
	return m_blinkEnd;
}

void FadeManager::SetScreenBlack()
{
	m_color = kBlack;
	m_color.A(1.0f);
}
