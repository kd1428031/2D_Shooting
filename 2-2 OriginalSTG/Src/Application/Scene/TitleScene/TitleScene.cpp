#include "TitleScene.h"
#include "../SceneManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/Fade/FadeManager.h"
#include "Application/Audio/AudioManager.h"

void TitleScene::Init()
{
	FADEMANAGER.Init();
	m_isExiting = false;

	m_background = SCENEMANAGER.GetBackground();
	m_background->Init();

	UIMANAGER.Init();      
	UIMANAGER.CreateUi(UiType::TitleName);
	UIMANAGER.CreateUi(UiType::PressStart);
	AUDIOM.FadeOutAndPlayNext(SoundName::kTitle, 0.2f, 1.0f, true);
	FADEMANAGER.FadeIn(1);
}

void TitleScene::Update(float dt)
{
	INPUT.Update();
	m_background->Update(dt);
	UIMANAGER.Update(dt);
	FADEMANAGER.Update(dt);
	AUDIOM.Update();
	AUDIOM.UpdateFade();

	if (INPUT.IsKeyTriggered(VK_RETURN))
	{
		UIMANAGER.Destroy(UiType::TitleName);
		UIMANAGER.Destroy(UiType::PressStart);
		AUDIOM.FadeOutAndPlayNext(SoundName::kGame, 1.0f, 1.0f, true);
		FADEMANAGER.FadeOut(1);
		AUDIOM.PlaySe(SoundName::kMenuPush);
		m_isExiting = true;
	}

	if (m_isExiting && !UIMANAGER.IsAlive(UiType::TitleName))
	{
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Draw()
{
	m_background->Draw();
	UIMANAGER.Draw();
	FADEMANAGER.Draw();
}
