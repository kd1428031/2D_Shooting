#include "UiBase.h"

UiBase::UiBase()
    : m_isAlive(true), m_scale(1.0f), m_angle(0.0f), m_alpha(1.0f), m_tex(nullptr)

{
}

void UiBase::Update(float dt)
{
    if (!m_isAlive)return;

    UpdateImpl(dt);
    UpdateMatrix();
}

void UiBase::Draw()
{
    if (!m_isAlive)return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ 
        (int)(m_animFrame.x * m_texFrameSize.x),(int)(m_animFrame.y * m_texFrameSize.y), 
        (int)m_texFrameSize.x, (int)m_texFrameSize.y }, m_alpha);

    DrawImpl();
}

void UiBase::UpdateMatrix()
{
    m_scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
    m_rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scaleMat * m_rotMat * m_transMat;
}
