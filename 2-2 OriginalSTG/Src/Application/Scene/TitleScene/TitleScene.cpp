#include "TitleScene.h"
#include "../SceneManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/Fade/FadeManager.h"

void TitleScene::Init()
{
	m_isExiting = false;

	m_background = SCENEMANAGER.GetBackground();
	m_background->Init();

	UIMANAGER.Init();      
	UIMANAGER.CreateUi(UiType::TitleName);
	UIMANAGER.CreateUi(UiType::GameStart);
}

void TitleScene::Update(float dt)
{
	INPUT.Update();
	m_background->Update(dt);
	UIMANAGER.Update(dt);
	FADEMANAGER.Update(dt);

	if (!m_isExiting && UIMANAGER.IsGameStartButton())
	{
		UIMANAGER.Destroy(UiType::TitleName);
		UIMANAGER.Destroy(UiType::GameStart);
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
