#include "GameObject.h"

GameObject::GameObject(Math::Vector2 pos, float scale)
    : m_pos(pos), m_scale(scale), m_angle(0.0f), m_alpha(1.0f),m_radius(0.0f),m_tex(nullptr)
{
}
