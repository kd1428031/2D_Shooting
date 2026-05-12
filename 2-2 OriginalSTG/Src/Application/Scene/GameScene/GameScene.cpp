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
#include "Application/Audio/AudioManager.h"

void GameScene::Init()
{
	FADEMANAGER.Init();
	m_background = SCENEMANAGER.GetBackground();

	TIMEMANAGER.Init();
	PLAYERMANAGER.Init();
	UIMANAGER.Init();
	UIMANAGER.CreateUi(UiType::Score);
	UIMANAGER.CreateUi(UiType::BomdWaitCounter);
	UIMANAGER.CreateUi(UiType::RavenBomdWaitCounter);

	ENEMYMANAGER.Init();
	BULLETMANAGER.Init();
	EFFCTMANAGER.Init();
	SCOREMANAGER.Init();

	m_timer = 0.0f;
	m_time = 0.0f;

	FADEMANAGER.FadeIn(1);
}

void GameScene::Update(float dt)
{
	// 大ボス
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

			m_wave = Wave::three;
			m_timer = 5.0f;
		}
	}
	else testKey = false;

	// 中ボス
	if (GetAsyncKeyState('I') & 0x8000)
	{
		if (!testKey2)
		{
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			//m_bossMakeFlg = true;
			m_enemyCreate = true;
			testKey2 = true;

			m_wave = Wave::oen;
			m_timer = 20.0f;
		}
	}
	else testKey2 = false;

	if (GetAsyncKeyState('O') & 0x8000)
	{
		if (!testKey3)
		{
			PLAYERMANAGER.GetPlayer()->SetGameoverFlg(true);
		}
	}
	else testKey3 = false;

	m_timer += dt;

	// ランダム生成
	switch (m_wave)
	{
	case GameScene::Wave::oen:
	{
		if (ENEMYMANAGER.GetEnemyNum() < 15)
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
			m_oneBoss->SetRadius(64);
			m_oneBoss->SetHp(750);
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
		if (ENEMYMANAGER.GetEnemyNum() < 30)
		{
			if (Random::Chance(0.05f))
			{
				EnemyType type = (EnemyType)Random::Range(0, 1);
				bool shotFlg = Random::Chance(0.3f);
				EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 4);

				ENEMYMANAGER.CreateEnemy(type,
					{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
					shotFlg, shotType);
			}
		}

		if (m_timer > 20.0f)
		{
			m_wave = Wave::three;
			m_timer = 0.0f;

			for (int i = 0; i < 50; i++)
			{
				EnemyType type = (EnemyType)Random::Range(0, 1);
				bool shotFlg = Random::Chance(0.3f);
				EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 4);

				ENEMYMANAGER.CreateEnemy(type,
					{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
					shotFlg, shotType);
			}
		}

		break;
	}

	case GameScene::Wave::three:
	{
		if (ENEMYMANAGER.GetEnemyNum() < 300)
		{
			/*if (Random::Chance(0.05f))
			{
				EnemyType type = (EnemyType)Random::Range(0, 1);
				bool shotFlg = Random::Chance(0.5f);
				EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 5);

				ENEMYMANAGER.CreateEnemy(type,
					{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
					shotFlg, shotType);
			}*/
		}

		if (ENEMYMANAGER.GetEnemyNum() <= 0)
		{
			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			m_bossMakeFlg = true;
			m_enemyCreate = true;

			m_wave = Wave::threeBoss;
			m_timer = 0.0f;

			AUDIOM.FadeOutBgm(1.5f);
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
				AUDIOM.FadeInBgm(SoundName::kLastboss, 2.0f);

			}
		}
		break;
	}
	}

	// ヒット時画面が赤く
	if (PLAYERMANAGER.GetPlayer()->IsIsHit() && PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		if (!m_sceneChangeFlg)
		{
			FADEMANAGER.Blink(0.2f, 1.0f, Math::Color(0.8f, 0.2f, 0.2f, 0.0f));
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
	AUDIOM.Update();
	AUDIOM.UpdateFade();

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
			UIMANAGER.Destroy(UiType::RavenBomdWaitCounter);
			SCENEMANAGER.SetNextScene(SceneManager::SceneType::Result);
			AUDIOM.FadeOutAndPlayNext(SoundName::kResult, 0.5f, 1.0f, true);
		}
	}
}

void GameScene::Draw()
{
	m_background->Draw();
	EFFCTMANAGER.DrawBack();
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