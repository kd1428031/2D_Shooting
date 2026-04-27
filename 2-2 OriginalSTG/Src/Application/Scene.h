#pragma once

class Scene
{
private:

	float m_scrollSpeed = kDefaultScrollSpeed;

	static constexpr float kDefaultScrollSpeed = 300.0f;
	static constexpr float kMinScrollSpeed = 250.0f;
	static constexpr float kMaxScrollSpeed = 700.0f;


public:

	const int screenWidth = 640;
	const int screenHeight = 360;

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	void ScrollSpeedChange(float dt);

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