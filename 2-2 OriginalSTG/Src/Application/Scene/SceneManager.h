#pragma once
#include "Application/GameObject/Background/Background.h"

class BaseScene;

class SceneManager
{
public:

	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	~SceneManager() { Release(); }

	enum class SceneType
	{
		Title,
		Game
	};
	
	void Init();
	void Update(float dt);
	void Draw();

	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	SceneType GetCurrentScene() const
	{
		return m_currentSceneType;
	}

	Background* GetBackground() { return m_background.get(); }

private:

	SceneManager() {}

	void Release();

	void ChangeScene(SceneType _sceneType);
	
	std::shared_ptr<BaseScene> m_currentScene;

	SceneType m_currentSceneType = SceneType::Title;
	SceneType m_nextSceneType = m_currentSceneType;

	std::unique_ptr<Background> m_background;

};
#define SCENEMANAGER SceneManager::GetInstance()