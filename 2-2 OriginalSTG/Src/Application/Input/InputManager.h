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

	void Reset();

private:

	InputManager(){}

	bool m_prevKey[256] = {};
	bool m_triggerKey[256] = {};

};
#define INPUT InputManager::GetInstance()