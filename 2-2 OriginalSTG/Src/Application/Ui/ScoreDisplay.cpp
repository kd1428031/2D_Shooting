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

	m_texFrameSize = kTexFrameSize;
	m_pos = kInitPos;
	m_scale = kInitScale;
	m_animFrame = {};
}

void ScoreDisplay::UpdateImpl(float dt)
{
}

void ScoreDisplay::Draw()
{
	if (!m_isAlive) return;

	int digits = 6;

	for (int i = 0; i < digits; i++)
	{
		int digitIndex = (SCOREMANAGER.GetScore() / (int)pow(10, digits - 1 - i)) % 10;
		float srcX = m_texFrameSize * digitIndex;

		SHADER.m_spriteShader.SetMatrix(CreateMatrix({(float)(i * (m_texFrameSize + kTexFrameOffSet)), 0 }));
		SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{
			(int)srcX, 0, m_texFrameSize, m_texFrameSize }, m_alpha);
	}
}

Math::Matrix ScoreDisplay::CreateMatrix(Math::Vector2 offset)
{
	Math::Matrix transMat;
	Math::Matrix rotMat;
	Math::Matrix scaleMat;
	Math::Matrix mat;

	scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
	rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
	transMat = Math::Matrix::CreateTranslation(m_pos.x + offset.x, m_pos.y + offset.y, 0);
	mat = scaleMat * rotMat * transMat;

	return mat;
}
