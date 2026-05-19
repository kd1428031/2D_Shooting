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

    void Init();
    void Update();

    void Stop() { m_isStopped = true; }
    void Start() { m_isStopped = false; }

    void HitStop(int frames);
    void SetSlow(float scale) { m_timeScale = scale; }
    void ResetSpeed() { m_timeScale = 1.0f; }

    float GetDeltaTime();

private:

    TimeManager() = default;

    bool m_isStopped = false;
};

#define TIMEMANAGER TimeManager::GetInstance()