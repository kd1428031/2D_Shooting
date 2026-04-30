#include "SceneManager.h"
#include "GameScene/GameScene.h"
#include "TitleScene/TitleScene.h"

void SceneManager::Init()
{
	m_background = std::make_unique<Background>();
	m_background->Init();
	ChangeScene(m_currentSceneType);
}

void SceneManager::Update(float dt)
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->Update(dt);
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;

	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	m_currentSceneType = _sceneType;
}
