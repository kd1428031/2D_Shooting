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
}

void GameScene::Update(float dt)
{
	// 採用検討
	//ScrollSpeedChange(dt);

	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey)
		{
			/*int rand = Random::Range(0, 1);
			bool shotFlg = Random::Chance(0.5f);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 3);

			if(rand == 0)
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f, Random::Range(-360.0f, 360.0f)}, shotFlg, shotType);

			if (rand == 1)
				ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f, Random::Range(-360.0f, 360.0f) },shotFlg, shotType);*/

			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			m_bossMakeFlg = true;
			m_enemyCreate = true;
			testKey = true;
		}
	}
	else testKey = false;

	if (!m_enemyCreate)
	{
		if (Random::Chance(0.5f))
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			int rand = Random::Range(0, 1);
			bool shotFlg = Random::Chance(0.5f);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 3);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },
				shotFlg, shotType);
		}
	}

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

	m_background->Update(dt);
	PLAYERMANAGER.Update(dt);
	ENEMYMANAGER.Update(dt);
	BULLETMANAGER.Update(dt);
	COLLISIONMANAGER.CheckAll(PLAYERMANAGER.GetPlayer(), ENEMYMANAGER.GetEnemy(), BULLETMANAGER.GetBullet());
	EFFCTMANAGER.Update(dt);
	UIMANAGER.Update(dt);
	FADEMANAGER.Update(dt);
	INPUT.Update();

	/*if (SCOREMANAGER.GetScore() >= 100)
	{
		if (!testFlg1)
		{
			UIMANAGER.CreateUi(UiType::WarningCutIn);
			TIMEMANAGER.HitStop(200);
			testFlg1 = true;
		}
	}*/

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


	if (!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		if (!m_sceneChangeFlg)
		{
			m_sceneChangeFlg = true;
			FADEMANAGER.FadeOut(1);
		}
	}

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
}