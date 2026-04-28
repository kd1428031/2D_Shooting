#include "Background.h"
#include "Application/ResourceManager.h"
#include "Application/Scene.h";

void Background::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kBgGame);
    m_pos = {};
    m_alpha = 1.0f;
    m_scale = 1.1f;
}

void Background::Update(float dt)
{
    m_pos.x += SCENE.GetScrollSpeed() * dt;

    // 1枚分スクロールしたらリセット
    if (m_pos.x >= kWidth * m_scale)
    {
        m_pos.x = 0.0f;
    }

    Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);

    m_mat = scaleMat * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat2 = scaleMat * Math::Matrix::CreateTranslation(m_pos.x - kWidth * m_scale, m_pos.y, 0);
}

void Background::Draw()
{
    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 0, 0, kWidth, kHeight }, m_alpha);

    SHADER.m_spriteShader.SetMatrix(m_mat2);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 0, 0, kWidth, kHeight }, m_alpha);
}
