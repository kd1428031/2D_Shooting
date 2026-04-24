#pragma once

class TimeManager
{
public:

    ~TimeManager() = default;

    static TimeManager& GetInstance()
    {
        static TimeManager instance;
        return instance;
    }

    float m_timeScale = 1.0f;
    int   m_stopFrames = 0;

    void Update();

    void HitStop(int frames);
    void SetSlow(float scale) { m_timeScale = scale; }
    void ResetSpeed() { m_timeScale = 1.0f; }

private:

    TimeManager() = default;
};

#define TIMEMANAGER TimeManager::GetInstance()