#include "InputManager.h"
#include "Application/Scene.h"
#include "Application/main.h"

bool InputManager::IsKeyHeld(int key) const
{
	return GetAsyncKeyState(key) & 0x8000;
}

POINT InputManager::GetMousePos()
{
	POINT mousePos;	//戻り値用

	GetCursorPos(&mousePos);	//←POINT型のアドレスを渡す

	//指定のウィンドウ基準のマウス座標に変換（実行画面の左上が(0,0)）
	ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

	//マウスの座標系を実行画面の座標系（中止が0,0）に補正
	mousePos.x -= SCENE.screenWidth / 2;
	mousePos.y -= SCENE.screenHeight / 2;
	mousePos.y *= -1;

	return mousePos;
}
