#include "RavenWaitCounter.h"
#include "Application/ResourceManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

RavenWaitCounter::RavenWaitCounter()
{
	Init();
}

void RavenWaitCounter::Init()
{
	m_tex = RESOURCEMANAGER.GetTex(TexName::kNumber);
	m_iconTex = RESOURCEMANAGER.GetTex(TexName::kRavenIcon);
	m_keyTex = RESOURCEMANAGER.GetTex(TexName::kC);

	m_pos = kInitPos;
	m_scale = kInitScale;
	m_color = kInitColor;
}

void RavenWaitCounter::UpdateImpl(float dt)
{
	Math::Vector2 pos = { kInitPos.x, -300 };
	m_iconMat = CreateMatrix(pos, { 0.25f,0.25f, }, 0.0f);

	Math::Vector2 pos2 = { kInitPos.x, -300 - 30 };
	m_keyMat = CreateMatrix(pos2, { 0.5f,0.5f, }, 0.0f);

	Player* player = PLAYERMANAGER.GetPlayer();

	if (player->GetRavenBomdWait() > 0 || player->GetMp() < 40 ||
		PLAYERMANAGER.GetRaven()->GetPowUpFlg())
	{
		m_iconColor.A(0.5f);
	}
	else
	{
		m_iconColor.A(1.0f);
	}
}

void RavenWaitCounter::Draw()
{
	if (!m_isAlive) return;

	SHADER.m_spriteShader.SetMatrix(m_iconMat);

	Math::Rectangle rect{ 0, 0, 128, 128 };
	SHADER.m_spriteShader.DrawTex_Color(m_iconTex, rect, m_iconColor);

	SHADER.m_spriteShader.SetMatrix(m_keyMat);
	rect = { 0, 0, 64, 64 };
	SHADER.m_spriteShader.DrawTex_Color(m_keyTex, rect, m_keyColor);

	if (PLAYERMANAGER.GetPlayer()->GetRavenBomdWait() > 0 && !PLAYERMANAGER.GetRaven()->GetPowUpFlg())
	{
		int digits = 2;

		for (int i = 0; i < digits; i++)
		{
			int digitIndex = (PLAYERMANAGER.GetPlayer()->GetRavenBomdWait() / (int)pow(10, digits - 1 - i)) % 10;
			float srcX = kTexFrameWidth * digitIndex;

			Math::Rectangle rect{
				(int)srcX, 0, kTexFrameWidth, kTexFrameHeight
			};

			SHADER.m_spriteShader.SetMatrix(CreateMatrix({ (float)(i * (kTexFrameWidth + kTexFrameOffSet)) + kCountPosOffSet, 0 }));
			SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
		}
	}
}
