#include "ScoreDisplay.h"
#include "Application/Scene.h"

ScoreDisplay::ScoreDisplay ()
{
	Init();
}

void ScoreDisplay::Init()
{
	m_pos = { -600, 250 };
	m_scale = 1.0f;
	m_animFrame = {};
}

void ScoreDisplay::DrawImpl()
{
	char text[200];

	sprintf_s(text, sizeof(text), "Score %d", SCENE.GetScore());

	SHADER.m_spriteShader.DrawString(m_pos.x, m_pos.y, text, m_color);
}