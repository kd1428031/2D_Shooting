#include "TimeManager.h"
#include "Application/main.h"

void TimeManager::Init()
{
    m_timeScale = 1.0f;
    m_stopFrames = 0.0f;
}

void TimeManager::Update()
{
    if (!m_isStopped)
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
    else
    {
        m_timeScale = 0.0f;
    }
}

void TimeManager::HitStop(int frames)
{
    if (frames > m_stopFrames)
    {
        m_stopFrames = frames;
    }
}

float TimeManager::GetDeltaTime()
{
    return APP.m_deltaTime * m_timeScale;
}
