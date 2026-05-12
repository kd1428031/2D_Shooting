#pragma once

class Scene
{
private:

	float m_scrollSpeed = kDefaultScrollSpeed;

	static constexpr float kDefaultScrollSpeed = 300.0f;
	static constexpr float kMinScrollSpeed = 250.0f;
	static constexpr float kMaxScrollSpeed = 700.0f;

	KdTexture* m_mouseTex;
	Math::Vector2 m_mouse;
	Math::Matrix m_mat;

public:

	const int screenWidth = 1280;
	const int screenHeight = 720;

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	void DrawCursor();

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