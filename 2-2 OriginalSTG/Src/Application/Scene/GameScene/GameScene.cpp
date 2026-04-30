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

void GameScene::Init()
{
	PLAYERMANAGER.Init();
	m_background = SCENEMANAGER.GetBackground();
	UIMANAGER.CreateUi(UiType::Score);
}

void GameScene::Update(float dt)
{
	// 採用検討
	//ScrollSpeedChange(dt);

	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!testKey)
		{
			ENEMYMANAGER.CreateEnemy({ 640, Random::Range(-360.0f, 360.0f) });
			/*UIMANAGER.CreateUi(UiType::WarningCutIn);
			TIMEMANAGER.HitStop(200);*/
			testKey = true;
		}
	}
	else testKey = false;

	if (rand() % 100 < 1)
	{
		//ENEMYMANAGER.CreateEnemy({ 640, (float)(rand() % 720 - 360) });
	}

	m_background->Update(dt);
	PLAYERMANAGER.Update(dt);
	ENEMYMANAGER.Update(dt);
	BULLETMANAGER.Update(dt);
	COLLISIONMANAGER.CheckAll(PLAYERMANAGER.GetPlayer(), ENEMYMANAGER.GetEnemy(), BULLETMANAGER.GetBullet());
	UIMANAGER.Update(dt);

	if (SCOREMANAGER.GetScore() >= 100)
	{
		if (!testFlg1)
		{
			UIMANAGER.CreateUi(UiType::WarningCutIn);
			TIMEMANAGER.HitStop(200);
			testFlg1 = true;
		}
	}

	if (!PLAYERMANAGER.GetPlayer()->IsAlive())
	{
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::Draw()
{
	m_background->Draw();
	PLAYERMANAGER.Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	UIMANAGER.Draw();
}