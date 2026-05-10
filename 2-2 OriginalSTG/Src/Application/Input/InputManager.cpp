#include "InputManager.h"
#include "Application/Scene.h"
#include "Application/main.h"

void InputManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		bool current = GetAsyncKeyState(i) & 0x8000;

		m_triggerKey[i] = current && !m_prevKey[i];
		m_prevKey[i] = current;
	}

	bool current = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
	m_triggerLeftClick = current && !m_prevLeftClick; // トリガーをここで確定
	m_prevLeftClick = current; // prevを更新
}

bool InputManager::IsKeyHeld(int key) const
{
	return GetAsyncKeyState(key) & 0x8000;
}

bool InputManager::IsKeyTriggered(int key) const
{
	return m_triggerKey[key];
}

bool InputManager::IsLeftClick() const
{
	return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
}

bool InputManager::IsRightClick() const
{
	return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

bool InputManager::IsTriggerLeftClick() const
{
	return m_triggerLeftClick;
}

void InputManager::Reset()
{
	memset(m_prevKey, 0, sizeof(m_prevKey));
	memset(m_triggerKey, 0, sizeof(m_triggerKey));
	m_prevLeftClick = false;
	m_triggerLeftClick = false;
}

POINT InputManager::GetMousePos()
{
	POINT mousePos;

	GetCursorPos(&mousePos);

	//指定のウィンドウ基準のマウス座標に変換（実行画面の左上が(0,0)）
	ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

	//マウスの座標系を実行画面の座標系（中止が0,0）に補正
	mousePos.x -= SCENE.screenWidth / 2;
	mousePos.y -= SCENE.screenHeight / 2;
	mousePos.y *= -1;

	return mousePos;
}
