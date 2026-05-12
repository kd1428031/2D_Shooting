#pragma once

class FadeManager
{
public:

    ~FadeManager() = default;

    static FadeManager& GetInstance()
    {
        static FadeManager instance;
        return instance;
    }

    void Init();
    void Update(float dt);
    void Draw();

    void FadeIn(float fadeSpeed, Math::Color color = {0,0,0,1,});
    void FadeOut(float fadeSpeed, Math::Color color = {0,0,0,0});

    bool IsFadeEnd();

    void Blink(float time, float speed, Math::Color color);
    bool IsBlinkEnd();

private:

    FadeManager() { Init(); };

    KdTexture* m_tex;
    Math::Matrix m_mat;

    const Math::Color kBlack = { 0,0,0,0 };

    Math::Color m_color;
    bool m_fadeInFlg;
    bool m_fadeOutFlg;
    bool m_fadeEndFlg;

    float m_fadeSpeed;

    bool m_blinkFlg = false;
    bool m_blink = false;
    bool m_blinkEnd = false;
    float m_timer = 0.0f;
};

#define FADEMANAGER FadeManager::GetInstance()