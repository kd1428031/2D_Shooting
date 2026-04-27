#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{

}

void TitleScene::Update(float dt)
{
	m_alpha += m_addAlpha;

	if (m_alpha > 1)
	{
		m_alpha = 1.0f;
		m_addAlpha *= -1;
	}
	else if(m_alpha < 0.0f)
	{
		m_alpha = 0.0f;
		m_addAlpha *= -1;
	}

}

void TitleScene::Draw()
{
}
