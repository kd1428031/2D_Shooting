#include "TitleScene.h"
#include "../SceneManager.h"
#include "Application/Input/InputManager.h"
#include "Application/Ui/UiManager.h"

void TitleScene::Init()
{
	m_background = SCENEMANAGER.GetBackground();
	m_background->Init();

	UIMANAGER.CreateUi(UiType::TitleName);
}

void TitleScene::Update(float dt)
{
	m_background->Update(dt);

	if (INPUT.IsKeyHeld(VK_RETURN))
	{
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Game);
		UIMANAGER.Destroy(UiType::TitleName);
	}
	UIMANAGER.Update(dt);
}

void TitleScene::Draw()
{
	m_background->Draw();
	UIMANAGER.Draw();
}
