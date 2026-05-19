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
}

bool InputManager::IsKeyHeld(int key) const
{
	return GetAsyncKeyState(key) & 0x8000;
}

bool InputManager::IsKeyTriggered(int key) const
{
	return m_triggerKey[key];
}

bool InputManager::IsAnyKeyTriggered() const
{
    static const int keys[] =
    {
        // アルファベット
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',

        // 数字
        '0','1','2','3','4','5','6','7','8','9',

        // 特殊
        VK_RETURN,
        VK_SPACE,
        VK_ESCAPE,
        
        // 修飾キー
        VK_SHIFT,
        VK_CONTROL,

        VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
        VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
        VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
        VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9
    };

    for (int key : keys)
    {
        if (IsKeyTriggered(key))
            return true;
    }

    return false;
}


void InputManager::Reset()
{
	memset(m_prevKey, 0, sizeof(m_prevKey));
	memset(m_triggerKey, 0, sizeof(m_triggerKey));
}
