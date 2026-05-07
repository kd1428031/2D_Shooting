#include "GameObject.h"

GameObject::GameObject(Math::Vector2 pos, float scale)
    : m_pos(pos), m_scale(scale), m_angle(0.0f), m_color(1.0f,1.0f,1.0f,1.0f), 
    m_alpha(1.0f),m_radius(0.0f), m_flipX(1.0f),
    m_animFrame(0.0f,0.0f), m_tex(nullptr)
{
}

void GameObject::UpdateMatrix()
{
    Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale * m_flipX, m_scale, 1);
    Math::Matrix rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = scaleMat * rotMat * transMat;
}
