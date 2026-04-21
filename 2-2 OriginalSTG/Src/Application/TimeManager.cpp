#include "TimeManager.h"

void TimeManager::Update()
{
    if (m_stopFrames > 0)
    {
        m_stopFrames--;
        m_timeScale = 0.0f;
    }
    else
    {
        m_timeScale = 1.0f;  // ストップ終了後に自動リセット
    }
}