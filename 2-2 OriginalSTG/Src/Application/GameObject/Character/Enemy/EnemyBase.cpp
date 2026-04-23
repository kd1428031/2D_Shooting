#include "EnemyBase.h"

EnemyBase::EnemyBase(Math::Vector2 pos, float scale)
    :Character(pos, scale), m_state(State::Alive)
{
}

void EnemyBase::Draw()
{
    if (m_state == State::Dead) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ (int)m_animFrame.x * m_texFrameSize,(int)m_animFrame.y * m_texFrameSize, m_texFrameSize, m_texFrameSize }, m_alpha);
}

void EnemyBase::Update(float dt)
{
    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }

    UpdateImpl(dt);
    Move(dt);
    UpdateMatrix();
}

void EnemyBase::Move(float dt)
{
    m_pos += m_velocity * dt;
}

void EnemyBase::TakeDamage(float damage)
{
    Character::TakeDamage(damage);
    if (m_hp <= 0) m_state = State::Dying;
}
