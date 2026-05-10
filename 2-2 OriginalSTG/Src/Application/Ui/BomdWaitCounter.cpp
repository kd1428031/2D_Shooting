#include "BomdWaitCounter.h"
#include "Application/ResourceManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

BomdWaitCounter::BomdWaitCounter()
{
	Init();
}

void BomdWaitCounter::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kNumber);
	m_iconTex = RESOURCEMANAGER.GetTex(TexName::kLightningIcon);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
}

void BomdWaitCounter::UpdateImpl(float dt)
{
	Math::Vector2 pos = { -350, -300 };
	m_iconMat = CreateMatrix(pos, { 0.25f,0.25f, }, 0.0f);

	if (PLAYERMANAGER.GetPlayer()->GetBomdWait() > 0)
	{
		m_iconColor.A(0.5f);
	}
	else
	{
		m_iconColor.A(1.0f);
	}
}

void BomdWaitCounter::Draw()
{
	if (!m_isAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_iconMat);

	Math::Rectangle rect{ 0, 0, 128, 128 };
	SHADER.m_spriteShader.DrawTex_Color(m_iconTex, rect, m_iconColor);

	if (PLAYERMANAGER.GetPlayer()->GetBomdWait() > 0)
	{
		int digits = 2;

		for (int i = 0; i < digits; i++)
		{
			int digitIndex = (PLAYERMANAGER.GetPlayer()->GetBomdWait() / (int)pow(10, digits - 1 - i)) % 10;
			float srcX = kTexFrameWidth * digitIndex;

			Math::Rectangle rect{
				(int)srcX, 0, kTexFrameWidth, kTexFrameHeight
			};

			SHADER.m_spriteShader.SetMatrix(CreateMatrix({ (float)(i * (kTexFrameWidth + kTexFrameOffSet)), 0 }));
			SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
		}
	}
}
