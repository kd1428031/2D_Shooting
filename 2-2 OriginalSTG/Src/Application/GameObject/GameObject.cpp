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

Math::Matrix GameObject::CreateMatrix(Math::Vector2 pos, Math::Vector2 size, float angle)
{
    Math::Matrix scaleMat = Math::Matrix::CreateScale(size.x, size.y, 1);
    Math::Matrix rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(angle));
    Math::Matrix transMat = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
    Math::Matrix mat = scaleMat * rotMat * transMat;
    return mat;
}

Math::Matrix GameObject::CreateMatrix(Math::Vector2 offset)
{
    Math::Matrix transMat;
    Math::Matrix rotMat;
    Math::Matrix scaleMat;
    Math::Matrix mat;

    scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
    rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    transMat = Math::Matrix::CreateTranslation(m_pos.x + offset.x, m_pos.y + offset.y, 0);
    mat = scaleMat * rotMat * transMat;

    return mat;
}

float GameObject::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
    float rad = atan2(dest.y - src.y, dest.x - src.x);
    float deg = DirectX::XMConvertToDegrees(rad);
    if (deg < 0) deg += 360.0f;
    return deg;
}
