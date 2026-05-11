#include "GameScene.h"
#include "Application/Scene/SceneManager.h"
#include "Application/CollisionManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Application/GameObject/Character/Enemy/EnemyManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/TimeManager.h"
#include "Application/Score/ScoreManager.h"
#include "Application/Random/Random.h"
#include "Application/Fade/FadeManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Effect/EffectManager.h"

void GameScene::Init()
{
	m_background = SCENEMANAGER.GetBackground();

	TIMEMANAGER.Init();
	PLAYERMANAGER.Init();
	UIMANAGER.Init();
	UIMANAGER.CreateUi(UiType::Score);
	UIMANAGER.CreateUi(UiType::BomdWaitCounter);

	ENEMYMANAGER.Init();
	BULLETMANAGER.Init();
	EFFCTMANAGER.Init();
	FADEMANAGER.Init();
	SCOREMANAGER.Init();

	m_timer = 10.0f;
	m_time = 0.0f;
}

void GameScene::Update(float dt)
{
	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey)
		{
			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			m_bossMakeFlg = true;
			m_enemyCreate = true;
			testKey = true;
		}
	}
	else testKey = false;

	m_timer += dt;

	// ランダム生成
	switch (m_wave)
	{
	case GameScene::Wave::oen:
	{
		if (Random::Chance(0.05f))
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			bool shotFlg = Random::Chance(0.1f);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 3);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
				shotFlg, shotType);
		}

		if (m_timer > 20.0f)
		{
			ENEMYMANAGER.AllDestroy();
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);

			EnemyType type = (EnemyType)0;
			bool shotFlg = false;
			EnemyBase::ShotType shotType = EnemyBase::ShotType::Rotate;

			m_oneBoss = ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), 0.0f },
				shotFlg, shotType);
			m_oneBoss->SetScale(2);
			m_oneBoss->SetHp(1500);
			m_oneBoss->SetVelocity({ -300, 0 });
			m_oneBoss->SetBulletSpeed(150.0f);
			m_oneBoss->SetBulletAngleSpeed(700);
			m_oneBoss->SetShotInterval(0.02f);
			m_oneBoss->SetStopPos({ 320.0f, 0.0f });

			m_wave = Wave::oenBoss;
			m_timer = 0.0f;
		}

		break;
	}
	case GameScene::Wave::oenBoss:
	{
		if (m_oneBoss != nullptr)
		{
			if (m_oneBoss->GetPos().x <= 320)
			{
				m_oneBoss->SetShotFlg(true);
			}

			if (!m_oneBoss->IsActive())
			{
				m_wave = Wave::two;
				m_timer = 0.0f;
			}
		}
		break;
	}
	case GameScene::Wave::two:
	{
		if (Random::Chance(0.075f))
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			bool shotFlg = Random::Chance(0.3f);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 4);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
				shotFlg, shotType);
		}

		if (m_timer > 20.0f)
		{
			m_wave = Wave::three;
			m_timer = 0.0f;
		}

		break;
	}

	case GameScene::Wave::three:
	{
		if (Random::Chance(0.5f))
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			bool shotFlg = Random::Chance(0.5f);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 5);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
				shotFlg, shotType);
		}

		if (m_timer > 5.0f)
		{
			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			m_bossMakeFlg = true;
			m_enemyCreate = true;

			m_wave = Wave::threeBoss;
			m_timer = 0.0f;
		}

		break;
	}
	case GameScene::Wave::threeBoss:
	{
		// ボス生成
		if (m_bossMakeFlg)
		{
			FADEMANAGER.Blink(1.9f, 3.0f, Math::Color(0.0f, 0.0f, 0.0f, 0.0f));
			m_bossMakeFlg = false;
			m_bossCreateFlg = true;
		}

		if (!m_bossMakeFlg && m_bossCreateFlg)
		{
			if (FADEMANAGER.IsBlinkEnd())
			{
				PLAYERMANAGER.GetPlayer()->SetActionFlg(true);

				ENEMYMANAGER.CreateEnemy(EnemyType::GrimReaper,
					{ 320.0f, 0.0f },
					true, EnemyBase::ShotType::Rotate, 4);
				m_bossCreateFlg = false;
				m_bossActiveFlg = true;
			}
		}
		break;
	}
	}

	// 更新
	m_background->Update(dt);
	PLAYERMANAGER.Update(dt);
	ENEMYMANAGER.Update(dt);
	BULLETMANAGER.Update(dt);
	COLLISIONMANAGER.CheckAll(PLAYERMANAGER.GetPlayer(), ENEMYMANAGER.GetEnemy(), BULLETMANAGER.GetBullet());
	EFFCTMANAGER.Update(dt);
	UIMANAGER.Update(dt);
	FADEMANAGER.Update(dt);
	INPUT.Update();

	// リザルトへ移行
	if (m_bossActiveFlg)
	{
		if (!ENEMYMANAGER.IsBossAlive())
		{
			ENEMYMANAGER.AllDestroy();
			if (!m_sceneChangeFlg)
			{
				m_sceneChangeFlg = true;
				FADEMANAGER.FadeOut(1);
			}
		}
	}

	// 自機死亡時リザルトへ
	if (!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		if (!m_sceneChangeFlg)
		{
			m_sceneChangeFlg = true;
			FADEMANAGER.FadeOut(1);
		}
	}

	// 共通リザルト移行処理
	if (m_sceneChangeFlg)
	{
		if (FADEMANAGER.IsFadeEnd())
		{
			UIMANAGER.Destroy(UiType::Score);
			UIMANAGER.Destroy(UiType::BomdWaitCounter);
			SCENEMANAGER.SetNextScene(SceneManager::SceneType::Result);
			FADEMANAGER.FadeIn(1);
		}
	}
}

void GameScene::Draw()
{
	m_background->Draw();
	PLAYERMANAGER.Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	EFFCTMANAGER.Draw();
	UIMANAGER.Draw();
	PLAYERMANAGER.DrawUi();
	FADEMANAGER.Draw();

	/*char text[200];

	sprintf_s(text, sizeof(text), "Time %.4f", m_timer);

	SHADER.m_spriteShader.DrawString(400, 320, text, Math::Vector4(1, 1, 0, 1));*/

}