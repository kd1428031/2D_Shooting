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

	void Update();

	bool IsKeyHeld(int key) const;
	bool IsLeftClick() const;
	bool IsTriggerLeftClick() const;

	//マウス座標
	POINT GetMousePos();

private:

	InputManager(){}

	POINT m_mousePos;

	bool m_prevLeftClick = false;
	bool m_triggerLeftClick = false;

};
#define INPUT InputManager::GetInstance()