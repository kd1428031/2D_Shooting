#pragma once

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

private:

	SceneManager() { Init(); }

	void Init();
	void Release();

	void ChangeScene(SceneType _sceneType);
	
	std::shared_ptr<BaseScene> m_currentScene;

	SceneType m_currentSceneType = SceneType::Game;
	SceneType m_nextSceneType = m_currentSceneType;

};
#define SCENEMANAGER SceneManager::GetInstance()