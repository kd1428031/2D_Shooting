#include "ItemBase.h"

ItemBase::ItemBase(Math::Vector2 pos, float scale)
    :GameObject(pos, scale), m_isAlive(true), m_lifeTimer(kLifeTimer)
{
    m_radius = 32.0f;
    m_color = Math::Color{ 1.0f, 1.0f, 1.0f, 1.0f };
}

ItemBase::~ItemBase()
{
}

void ItemBase::Update(float dt)
{
    UpdateImpl(dt);
    CreateMatrix(m_pos, { m_scale, m_scale }, 0);
}

void ItemBase::Draw()
{
    Math::Rectangle rect{
            (int)m_animFrame.x * m_texFrameWidth,(int)m_animFrame.y * m_texFrameHeight,
            m_texFrameWidth, m_texFrameHeight
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void ItemBase::Destroy()
{
    m_isAlive = false;
}
