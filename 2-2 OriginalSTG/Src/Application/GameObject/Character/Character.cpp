#include "Character.h"

Character::Character(Math::Vector2 pos, float scale)
    :GameObject(pos, scale)
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