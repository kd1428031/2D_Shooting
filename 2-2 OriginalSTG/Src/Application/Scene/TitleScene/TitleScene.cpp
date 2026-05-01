#include "TitleScene.h"
#include "../SceneManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/Fade/FadeManager.h"

void TitleScene::Init()
{
	m_background = SCENEMANAGER.GetBackground();
	m_background->Init();

	UIMANAGER.Init();      
	UIMANAGER.CreateUi(UiType::TitleName);
}

void TitleScene::Update(float dt)
{
	m_background->Update(dt);

	if (INPUT.IsKeyHeld(VK_RETURN))
	{
		UIMANAGER.Destroy(UiType::TitleName);
	}

	if (!UIMANAGER.IsAlive(UiType::TitleName))
	{
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Game);
	}
	UIMANAGER.Update(dt);
	FADEMANAGER.Update(dt);
}

void TitleScene::Draw()
{
	m_background->Draw();
	UIMANAGER.Draw();
	FADEMANAGER.Draw();
}
