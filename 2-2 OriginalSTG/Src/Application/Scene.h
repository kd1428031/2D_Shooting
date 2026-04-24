#pragma once
#include "GameObject/Character/Player/Player.h"
#include "GameObject/Background/Background.h"

class Scene
{
private:

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Background> m_background;
	
	float m_scrollSpeed = kDefaultScrollSpeed;

	static constexpr float kDefaultScrollSpeed = 300.0f;
	static constexpr float kMinScrollSpeed = 250.0f;
	static constexpr float kMaxScrollSpeed = 700.0f;


public:

	const int screenWidth = 640;
	const int screenHeight = 360;

	bool testKey = false;

	int m_score;

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	void ScrollSpeedChange(float dt);

	int GetScore() const { return m_score; }

	void AddScore(int score) { m_score += score; }

	float GetScrollSpeed() const { return m_scrollSpeed; }

	// GUIˆ—
	void ImGuiUpdate();

private:

	Scene() {}


public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()