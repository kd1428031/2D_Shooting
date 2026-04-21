#include "Character.h"

Character::Character(Math::Vector2 pos, float scale)
    : m_pos(pos), m_scale(scale), m_angle(0.0f), m_alpha(1.0f)
{
}

void Character::TakeDamage(float damage)
{
    m_hp -= damage;

    if (m_hp <= 0)
    {
        m_hp = 0;
    }
}