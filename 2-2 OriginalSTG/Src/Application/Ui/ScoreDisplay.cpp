#include "ScoreDisplay.h"
#include "Application/Score/ScoreManager.h"
#include "Application/ResourceManager.h"
#include "Application/Score/ScoreManager.h"

ScoreDisplay::ScoreDisplay ()
{
	Init();
}

void ScoreDisplay::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kNumber);

	m_texFrameSize = { 256,360 };
	m_pos = kInitPos;
	m_scale = kInitScale;
	m_animFrame = {};

}

void ScoreDisplay::UpdateImpl(float dt)
{
	m_scoreDisplay = SCOREMANAGER.GetScore();


	m_texFrameSize *= m_digitIndex;
}

void ScoreDisplay::DrawImpl()
{
	/*char text[200];

	sprintf_s(text, sizeof(text), "Score %d", SCOREMANAGER.GetScore());

	SHADER.m_spriteShader.DrawString(m_pos.x, m_pos.y, text, m_color);*/
}