#pragma once

class Player;

class Scene
{
private:

	Player *player;

	
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