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

    void FadeIn(float fadeSpeed);
    void FadeOut(float fadeSpeed);

    bool IsFadeEnd();

private:

    FadeManager() = default;

    KdTexture* m_tex;
    Math::Matrix m_mat;

    const Math::Color kBlack = { 0,0,0,0 };

    Math::Color m_color;
    bool m_fadeInFlg;
    bool m_fadeOutFlg;
    bool m_fadeEndFlg;

    float m_fadeSpeed;
};

#define FADEMANAGER FadeManager::GetInstance()