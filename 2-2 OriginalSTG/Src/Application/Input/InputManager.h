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
	bool IsKeyTriggered(int key) const;
	bool IsLeftClick() const;
	bool IsRightClick() const;
	bool IsTriggerLeftClick() const;

	void Reset();

	//マウス座標
	POINT GetMousePos();

	POINT GetMousePosRaw();

private:

	InputManager(){}

	POINT m_mousePos;

	bool m_prevLeftClick = false;
	bool m_triggerLeftClick = false;

	bool m_prevKey[256] = {};
	bool m_triggerKey[256] = {};

};
#define INPUT InputManager::GetInstance()