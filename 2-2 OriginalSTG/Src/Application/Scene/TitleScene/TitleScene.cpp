#include "TitleScene.h"
#include "../SceneManager.h"
#include "Application/Input/InputManager.h"

void TitleScene::Init()
{
	m_background = SCENEMANAGER.GetBackground();
	m_background->Init();
}

void TitleScene::Update(float dt)
{
	m_background->Update(dt);

	if (INPUT.IsKeyHeld(VK_RETURN))
	{
		SCENEMANAGER.SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Draw()
{
	m_background->Draw();
}
