#include "Bullet.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Bullet::Bullet(Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
    : m_pos(pos), m_velocity(velocity), m_scale(scale),m_color(color)
{
}

void Bullet::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kBullet);

    m_isAlive = true;
    m_invincibleTimer = 0.0f;
    m_angle = 0.0f;
}

void Bullet::Update(float dt)
{
    if (!m_isAlive) return;

    // 移動
    m_pos += m_velocity * dt;

    // 無敵時間
    if (m_invincibleTimer > 0.0f)
    {
        m_invincibleTimer -= dt;
    }

    // 画面外チェック
    if (m_pos.x > SCENE.screenWidth + kDeleteMargin || m_pos.y > SCENE.screenHeight + kDeleteMargin ||
        m_pos.x < -SCENE.screenWidth - kDeleteMargin || m_pos.y < -SCENE.screenHeight - kDeleteMargin)
    {
        m_isAlive = false;
    }

    m_scaleMat = Math::Matrix::CreateScale(m_scale);
    m_rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scaleMat * m_transMat;
}

void Bullet::Draw()
{
    if (!m_isAlive) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, Math::Rectangle{ 0, kTexOffsetY, kTexFrameSize, kTexFrameSize }, m_color);
}

void Bullet::Destroy()
{
    m_isAlive = false;
}
