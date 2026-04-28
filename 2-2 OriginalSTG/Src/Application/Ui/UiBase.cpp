#include "UiBase.h"

UiBase::UiBase()
    : m_isAlive(true), m_scale(1.0f), m_angle(0.0f), m_tex(nullptr)
{
}

void UiBase::Update(float dt)
{
    if (!m_isAlive)return;

    UpdateImpl(dt);
    UpdateMatrix();
}

void UiBase::UpdateMatrix()
{
    Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
    Math::Matrix rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = scaleMat * rotMat * transMat;
}