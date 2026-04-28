#include "ScoreDisplay.h"
#include "Application/Score/ScoreManager.h"
#include "Application/ResourceManager.h"

ScoreDisplay::ScoreDisplay ()
{
	Init();
}

void ScoreDisplay::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kNumber);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
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
		float srcX = kTexFrameWidth * digitIndex;

		Math::Rectangle rect{
			(int)srcX, 0, kTexFrameWidth, kTexFrameHeight
		};

		SHADER.m_spriteShader.SetMatrix(CreateMatrix({(float)(i * (kTexFrameWidth + kTexFrameOffSet)), 0 }));
		SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
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
