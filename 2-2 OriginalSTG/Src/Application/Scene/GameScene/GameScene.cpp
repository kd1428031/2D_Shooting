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
#include "Application/ResourceManager.h"

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

	FADEMANAGER.FadeIn(kFadeTime);

	ChangePhase(Phase::Phase1);

	m_tutorialShotTex = RESOURCEMANAGER.GetTex(TexName::kTutorial_shot);
}

void GameScene::Update(float dt)
{
	// デバッグ用　必ずリリース時消す=========================
	DebugKey(dt);


	m_phaseTimer += dt;
	m_spawnTimer += dt;

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

	// ヒット時画面点滅
	if (PLAYERMANAGER.GetPlayer()->IsHit() && PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		FADEMANAGER.Blink(kHitBlinkTime, kHitBlinkSpeed, kHitBlinkColor);
	}

	// 自機死亡時リザルト移行
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

	m_tutorialShotMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0) *
		Math::Matrix::CreateTranslation(-420, -340, 1);
}

void GameScene::Draw()
{
	m_background->Draw();
	EFFCTMANAGER.DrawBack();
	PLAYERMANAGER.Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	EFFCTMANAGER.Draw();

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -320, 640, 40, &Math::Color(0, 0, 0, 0.75f), true);

	UIMANAGER.Draw();
	PLAYERMANAGER.DrawUi();

	Math::Rectangle rect = { 0, 0, 896, 64 };
	SHADER.m_spriteShader.SetMatrix(m_tutorialShotMat);
	SHADER.m_spriteShader.DrawTex_Color(m_tutorialShotTex, rect, m_color);

	EFFCTMANAGER.DrawFront();
	FADEMANAGER.Draw();

	// デバッグ用　必ずリリース時消す=========================
	DrawDebug();
}

void GameScene::UpdatePhase1(float dt)
{
	const auto& param = GetPhaseParam(m_phase);

	if (m_phaseTimer < param.spawnEndTime)
	{
		// 敵全滅か一定時間経過で敵生成
		if (ENEMYMANAGER.GetEnemyNum() <= 0 || m_spawnTimer > param.spawnInterval)
		{
			EnemyBase::ShotType shotType = EnemyBase::ShotType::Straight;
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 220.0f }, shotType);
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, 0.0f }, shotType);
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 100.0f, -220.0f }, shotType);

			shotType = EnemyBase::ShotType::Aimed;
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, 150.0f }, shotType);
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, -150.0f }, shotType);
	
			m_spawnTimer = 0.0f;
		}
	}

	// 一定時間経過後敵全滅でフェーズ移行
	if (ENEMYMANAGER.GetEnemyNum() <= 0 && m_phaseTimer > param.spawnEndTime)
	{
		ChangePhase(Phase::Phase1Boss);
	}

	// 一定時間経過でフェーズ強制移行
	if (m_phaseTimer > param.timeLimit)
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
	const auto& param = GetPhaseParam(m_phase);

	if (m_phaseTimer < param.spawnEndTime)
	{
		// 敵全滅か一定時間経過で敵生成
		if (ENEMYMANAGER.GetEnemyNum() <= 0 || m_spawnTimer > param.spawnInterval)
		{
			EnemyBase::ShotType shotType = EnemyBase::ShotType::Rotate;
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, 150.0f }, shotType)->SetShotInterval(0.2f);
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, -150.0f },shotType)->SetShotInterval(0.2f);
		
			shotType = EnemyBase::ShotType::AllRange;
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 150.0f, 220.0f }, shotType)->SetShotAllNWay(8);
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 150.0f, -220.0f },shotType)->SetShotAllNWay(8);
		
			m_spawnTimer = 0.0f;
		}
	}

	// 一定時間経過後敵全滅でフェーズ移行
	if (ENEMYMANAGER.GetEnemyNum() <= 0 && m_phaseTimer > param.spawnEndTime)
	{
		ChangePhase(Phase::Phase3);
	}

	// 一定時間経過でフェーズ強制移行
	if (m_phaseTimer > param.timeLimit)
	{
		ChangePhase(Phase::Phase3);
	}
}

void GameScene::UpdatePhase3(float dt)
{
	const auto& param = GetPhaseParam(m_phase);

	if (m_phaseTimer < param.spawnEndTime)
	{
		// 敵全滅か一定時間経過で敵生成
		if (ENEMYMANAGER.GetEnemyNum() <= 0 || m_spawnTimer > param.spawnInterval)
		{
			EnemyBase::ShotType shotType = EnemyBase::ShotType::Aimed;
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, 150.0f }, shotType)->SetShotInterval(0.5f);
			ENEMYMANAGER.CreateEnemy(EnemyType::Bat, { 640.0f + 50.0f, -150.0f }, shotType)->SetShotInterval(0.5f);

			shotType = EnemyBase::ShotType::AllRange;
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 150.0f, 220.0f }, shotType)->SetShotAllNWay(5);
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 150.0f, -220.0f }, shotType)->SetShotAllNWay(5);
		
			shotType = EnemyBase::ShotType::Aimed;
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 125.0f, 75.0f }, shotType)->SetShotInterval(0.75f);
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 125.0f, -75.0f }, shotType)->SetShotInterval(0.75f);
			
			shotType = EnemyBase::ShotType::Straight;
			ENEMYMANAGER.CreateEnemy(EnemyType::Daemon, { 640.0f + 50.0f, 0.0f }, shotType);

			m_spawnTimer = 0.0f;
		}
	}

	// 一定時間経過後敵全滅でフェーズ移行
	if (ENEMYMANAGER.GetEnemyNum() <= 0 && m_phaseTimer > param.spawnEndTime)
	{
		ChangePhase(Phase::FinalBossIntro);
	}

	// 一定時間経過でフェーズ強制移行
	if (m_phaseTimer > param.timeLimit)
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
		FADEMANAGER.FadeOut(kFadeTime);

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
	m_spawnTimer = 0.0f;

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

		EnemyType type = EnemyType::Daemon;
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

const GameScene::PhaseParam& GameScene::GetPhaseParam(Phase phase) const
{
	return kPhaseParams[(int)phase];
}

void GameScene::IsGameOver()
{
	if (m_phase != Phase::GameOver && m_phase != Phase::GameClear &&
		!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		FADEMANAGER.FadeOut(kFadeTime);
		ChangePhase(Phase::GameOver);
	}
}

void GameScene::DebugKey(float dt)
{
	// フェーズ1
	if (GetAsyncKeyState('T') & 0x8000)
	{
		if (!testKey)
		{
			PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey = true;

			ChangePhase(Phase::Phase1);
		}
	}
	else testKey = false;

	// フェーズ1Boss
	if (GetAsyncKeyState('Y') & 0x8000)
	{
		if (!testKey2)
		{
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey2 = true;

			ChangePhase(Phase::Phase1Boss);
		}
	}
	else testKey2 = false;

	// フェーズ1Boss
	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey2)
		{
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey2 = true;

			ChangePhase(Phase::Phase2);
		}
	}
	else testKey2 = false;

	if (GetAsyncKeyState('I') & 0x8000)
	{
		if (!testKey2)
		{
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey2 = true;

			ChangePhase(Phase::Phase3);
		}
	}
	else testKey2 = false;

	if (GetAsyncKeyState('O') & 0x8000)
	{
		if (!testKey2)
		{
			BULLETMANAGER.AllDestroy(BulletOwner::Enemy);
			ENEMYMANAGER.AllDestroy();
			testKey2 = true;

			ChangePhase(Phase::FinalBossIntro);
		}
	}
	// 自機無敵解除
	if (GetAsyncKeyState('L') & 0x8000)
	{
		if (!testKey3)
		{
			PLAYERMANAGER.GetPlayer()->SetGameoverFlg(true);
		}
	}
	else testKey3 = false;
}

void GameScene::DrawDebug()
{
	char PhaseTime[200];

	sprintf_s(PhaseTime, sizeof(PhaseTime), "PhaseTime %.3f", m_phaseTimer);

	SHADER.m_spriteShader.DrawString(340, 320, PhaseTime, Math::Vector4(1, 1, 0, 1));

	char SpawnTime[200];

	sprintf_s(SpawnTime, sizeof(SpawnTime), "SpawnTime %.3f", m_spawnTimer);

	SHADER.m_spriteShader.DrawString(340, 270, SpawnTime, Math::Vector4(1, 1, 0, 1));
}
