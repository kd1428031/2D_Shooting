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


void InputManager::Reset()
{
	memset(m_prevKey, 0, sizeof(m_prevKey));
	memset(m_triggerKey, 0, sizeof(m_triggerKey));
}
