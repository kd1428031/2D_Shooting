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

	FADEMANAGER.FadeIn(1);

	ChangePhase(Phase::Phase1);
}

void GameScene::Update(float dt)
{
	// デバッグキー　以下はリリース時消す=========================
	// 大ボス
	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey)
		{
			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey = true;

			ChangePhase(Phase::Phase3);
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
			testKey2 = true;

			ChangePhase(Phase::Phase1);
		}
	}
	else testKey2 = false;

	// 自機無敵解除
	if (GetAsyncKeyState('O') & 0x8000)
	{
		if (!testKey3)
		{
			PLAYERMANAGER.GetPlayer()->SetGameoverFlg(true);
		}
	}
	else testKey3 = false;

	// 以上はリリース時消す=====================================


	m_phaseTimer += dt;

	switch (m_phase)
	{
	case GameScene::Phase::Phase1:

		UpdatePhase1(dt);
		break;

	case GameScene::Phase::Phase1Boss:

		UpdatePhase1Boss(dt);
		break;

	case GameScene::Phase::Phase2:

		UpdatePhase2(dt);
		break;

	case GameScene::Phase::Phase3:

		UpdatePhase3(dt);
		break;

	case GameScene::Phase::FinalBossIntro:

		UpdateFinalBossIntro(dt);
		break;

	case GameScene::Phase::FinalBoss:

		UpdateFinalBoss(dt);
		break;

	case GameScene::Phase::GameClear:

		UpdateGameClear(dt);
		break;

	case GameScene::Phase::GameOver:

		UpdateGameOver(dt);
		break;
	}

	// ヒット時画面が赤く
	if (PLAYERMANAGER.GetPlayer()->IsIsHit() && PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		FADEMANAGER.Blink(0.2f, 1.0f, Math::Color(0.8f, 0.2f, 0.2f, 0.0f));
	}

	// 自機死亡時リザルトへ
	IsGameOver();

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

	// 以下デバッグ用
	char text[200];

	sprintf_s(text, sizeof(text), "Time %.4f", m_phaseTimer);

	SHADER.m_spriteShader.DrawString(400, 320, text, Math::Vector4(1, 1, 0, 1));
}

void GameScene::UpdatePhase1(float dt)
{
	if (m_phaseTimer > 10.0f)
	{
		EnemyBase::ShotType shotType = EnemyBase::ShotType::Straight;
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 300.0f }, shotType);
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 0.0f }, shotType);
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, -300.0f }, shotType);

		shotType = EnemyBase::ShotType::Aimed;
		ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, 150.0f }, shotType);
		ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, -150.0f }, shotType);
	}

	if (ENEMYMANAGER.GetEnemyNum() <= 0 || m_phaseTimer > 10000.0f)
	{
		ChangePhase(Phase::Phase1Boss);
	}
}

void GameScene::UpdatePhase1Boss(float dt)
{
	if (m_oneBoss != nullptr)
	{
		if (m_oneBoss->GetPos().x <= 320)
		{
			m_oneBoss->SetShotType(EnemyBase::ShotType::Rotate);
		}

		if (!m_oneBoss->IsActive())
		{
			ChangePhase(Phase::Phase2);
		}
	}
}

void GameScene::UpdatePhase2(float dt)
{
	if (ENEMYMANAGER.GetEnemyNum() < 30)
	{
		if (Random::Chance(0.05f))
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 4);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },shotType);
		}
	}

	if (m_phaseTimer > 20.0f)
	{
		ChangePhase(Phase::Phase3);

		for (int i = 0; i < 50; i++)
		{
			EnemyType type = (EnemyType)Random::Range(0, 1);
			EnemyBase::ShotType shotType = (EnemyBase::ShotType)Random::Range(0, 4);

			ENEMYMANAGER.CreateEnemy(type,
				{ 640.0f + Random::Range(60.0f, 120.0), Random::Range(-360.0f, 360.0f) },shotType);
		}
	}
}

void GameScene::UpdatePhase3(float dt)
{
	if (ENEMYMANAGER.GetEnemyNum() <= 0)
	{
		ChangePhase(Phase::FinalBossIntro);
	}
}

void GameScene::UpdateFinalBossIntro(float dt)
{
	if (FADEMANAGER.IsBlinkEnd())
	{
		ChangePhase(Phase::FinalBoss);
	}
}

void GameScene::UpdateFinalBoss(float dt)
{
	// ボス死亡時リザルトへ移行
	if (!ENEMYMANAGER.IsBossAlive())
	{
		ENEMYMANAGER.AllDestroy();
		FADEMANAGER.FadeOut(1);

		ChangePhase(Phase::GameClear);
	}
}

void GameScene::UpdateGameClear(float dt)
{
	// リザルト移行
	if (FADEMANAGER.IsFadeEnd())
	{
		UIMANAGER.Destroy(UiType::Score);
		UIMANAGER.Destroy(UiType::BomdWaitCounter);
		UIMANAGER.Destroy(UiType::RavenBomdWaitCounter);
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Result);
		AUDIOM.FadeOutAndPlayNext(SoundName::kResult, 0.5f, 1.0f, true);
	}
}

void GameScene::UpdateGameOver(float dt)
{
	// リザルト移行
	if (FADEMANAGER.IsFadeEnd())
	{
		UIMANAGER.Destroy(UiType::Score);
		UIMANAGER.Destroy(UiType::BomdWaitCounter);
		UIMANAGER.Destroy(UiType::RavenBomdWaitCounter);
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Result);
		AUDIOM.FadeOutAndPlayNext(SoundName::kResult, 0.5f, 1.0f, true);
	}
}

void GameScene::ChangePhase(Phase phase)
{
	m_phase = phase;
	m_phaseTimer = 0.0f;

	switch (phase)
	{
	case Phase::Phase1:
	{
		EnemyBase::ShotType shotType = EnemyBase::ShotType::None;
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 0.0f }, shotType);
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 150.0f }, shotType);
		ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, -150.0f }, shotType);

		 break;
	}

	case Phase::Phase1Boss:
	{
		ENEMYMANAGER.AllDestroy();
		BULLETMANAGER.AllDestroy(BulletOwner::Enemy);

		EnemyType type = (EnemyType)0;
		EnemyBase::ShotType shotType = EnemyBase::ShotType::None;

		m_oneBoss = ENEMYMANAGER.CreateEnemy(type,
			{ 640.0f + Random::Range(60.0f, 120.0), 0.0f },shotType);
		m_oneBoss->SetScale(2);
		m_oneBoss->SetRadius(64);
		m_oneBoss->SetHp(750);
		m_oneBoss->SetVelocity({ -300, 0 });
		m_oneBoss->SetBulletSpeed(150.0f);
		m_oneBoss->SetBulletAngleSpeed(700);
		m_oneBoss->SetShotInterval(0.02f);
		m_oneBoss->SetStopPos({ 320.0f, 0.0f });
		break;
	}
	case Phase::FinalBossIntro:
		PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
		BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
		ENEMYMANAGER.AllDestroy();
		AUDIOM.FadeOutBgm(1.5f);
		FADEMANAGER.Blink(1.9f, 3.0f, Math::Color(0.0f, 0.0f, 0.0f, 0.0f));
		break;

	case Phase::FinalBoss:
		PLAYERMANAGER.GetPlayer()->SetActionFlg(true);
		ENEMYMANAGER.CreateEnemy(EnemyType::GrimReaper,
			{ 320.0f, 0.0f },EnemyBase::ShotType::Rotate, 4);
		AUDIOM.FadeInBgm(SoundName::kLastboss, 2.0f);
		break;
	}
}

void GameScene::IsGameOver()
{
	if (m_phase != Phase::GameOver && m_phase != Phase::GameClear &&
		!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		FADEMANAGER.FadeOut(1);
		ChangePhase(Phase::GameOver);
	}
}
