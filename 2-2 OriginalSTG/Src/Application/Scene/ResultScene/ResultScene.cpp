#include "ResultScene.h"
#include "Application/Scene/SceneManager.h"
#include "Application/CollisionManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Application/GameObject/Character/Enemy/EnemyManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/Ui/ScoreDisplay.h"
#include "Application/TimeManager.h"
#include "Application/Score/ScoreManager.h"
#include "Application/Random/Random.h"
#include "Application/Fade/FadeManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Audio/AudioManager.h"

void ResultScene::Init()
{
	FADEMANAGER.Init();
	m_background = SCENEMANAGER.GetBackground();

	UIMANAGER.Init();
	UIMANAGER.CreateUi(UiType::Score);
	UIMANAGER.SetPos(UiType::Score, { -300,0 });
	UIMANAGER.SetScale(UiType::Score, 1);
	auto* score = static_cast<ScoreDisplay*>(UIMANAGER.GetUi(UiType::Score));
	score->SetOffSet(0);

	UIMANAGER.CreateUi(UiType::ScoreText);
	UIMANAGER.SetPos(UiType::ScoreText, { 0,200 });
	UIMANAGER.SetScale(UiType::ScoreText, 1);

	UIMANAGER.CreateUi(UiType::PressStart);

	PLAYERMANAGER.GetPlayer()->SetActionFlg(false);
	FADEMANAGER.FadeIn(kFadeTime);
}

void ResultScene::Update(float dt)
{
	TIMEMANAGER.Stop();
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

	if (INPUT.IsKeyTriggered(VK_RETURN))
	{
		if (!m_sceneChangeFlg)
		{
			m_sceneChangeFlg = true;
			FADEMANAGER.FadeOut(kFadeTime);
		}
	}

	if (m_sceneChangeFlg)
	{
		if (FADEMANAGER.IsFadeEnd())
		{
			TIMEMANAGER.Start();
			UIMANAGER.Destroy(UiType::Score);
			SCENEMANAGER.SetNextScene(SceneManager::SceneType::Title);
		}
	}
}

void ResultScene::Draw()
{
	m_background->Draw();
	PLAYERMANAGER.Draw();
	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	EFFCTMANAGER.Draw();

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &Math::Color(0, 0, 0, 0.5f), true);

	UIMANAGER.Draw();
	//PLAYERMANAGER.DrawUi();
	FADEMANAGER.Draw();
}