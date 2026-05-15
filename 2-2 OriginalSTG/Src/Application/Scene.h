#pragma once

class Scene
{
private:

public:

	int GetScreenWidth() const { return m_screenWidth; }
	int GetScreenHeight() const { return m_screenHeight; }

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

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

	static constexpr int m_screenWidth = 1280;
	static constexpr int m_screenHeight = 720;
};

#define SCENE Scene::GetInstance()