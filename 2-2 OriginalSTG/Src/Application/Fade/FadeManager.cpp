#include "FadeManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

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
		m_color.A(m_color.A() - (m_fadeSpeed * dt));
		if (m_color.A() <= 0)
		{
			m_fadeInFlg = false;
			m_fadeEndFlg = true;
		}
	}
	else if (m_fadeOutFlg)
	{
		m_color.A(m_color.A() + (m_fadeSpeed * dt));
		if (m_color.A() >= 1)
		{
			m_fadeOutFlg = false;
			m_fadeEndFlg = true;
		}
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(SCENE.screenWidth, SCENE.screenHeight, 1);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mat = scaleMat * transMat;
}

void FadeManager::Draw()
{
	Math::Rectangle rect = { 0,0,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void FadeManager::FadeIn(float fadeSpeed)
{
	m_color.A(1.0f);
	m_fadeInFlg = true;
	m_fadeEndFlg = false;
	m_fadeSpeed = fadeSpeed;
}

void FadeManager::FadeOut(float fadeSpeed)
{
	m_color.A(0.0f);
	m_fadeOutFlg = true;
	m_fadeEndFlg = false;
	m_fadeSpeed = fadeSpeed;
}

bool FadeManager::IsFadeEnd()
{
	return m_fadeEndFlg;
}
