#include "GameObject.h"

GameObject::GameObject(Math::Vector2 pos, float scale)
    : m_pos(pos), m_scale(scale), m_angle(0.0f), m_alpha(1.0f),m_radius(0.0f),m_tex(nullptr)
{
}

void GameObject::UpdateMatrix()
{
    m_scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
    m_rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scaleMat * m_rotMat * m_transMat;
}
