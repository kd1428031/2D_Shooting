#pragma once

class InputManager
{
public:

	// インスタンス取得用
	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	~InputManager(){}

	bool IsKeyHeld(int key) const;

	//マウス座標
	POINT GetMousePos();

private:

	InputManager(){}

	POINT m_mousePos;

};
#define INPUT InputManager::GetInstance()