#include "Bullet.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Bullet::Bullet(BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
    : GameObject(pos, scale), m_type(type), m_isAlive(true)
{
    m_radius = kRadius;
    m_velocity = velocity;
    m_color = color;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kBullet);
}

void Bullet::Update(float dt)
{
    if (!m_isAlive) return;

    Move(dt);

    UpdateMatrix();
}

void Bullet::Draw()
{
    if (!m_isAlive) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, Math::Rectangle{ 0, kTexOffsetY, kTexFrameSize, kTexFrameSize }, m_color);
}

void Bullet::Move(float dt)
{
    m_pos += m_velocity * dt;

    // 画面外チェック
    if (m_pos.x > SCENE.screenWidth + kDeleteMargin || m_pos.y > SCENE.screenHeight + kDeleteMargin ||
        m_pos.x < -SCENE.screenWidth - kDeleteMargin || m_pos.y < -SCENE.screenHeight - kDeleteMargin)
    {
        m_isAlive = false;
    }
}

void Bullet::UpdateMatrix()
{
    m_scaleMat = Math::Matrix::CreateScale(m_scale);
    m_rotMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
    m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_mat = m_scaleMat * m_rotMat * m_transMat;
}

void Bullet::Destroy()
{
    m_isAlive = false;
}

bool Bullet::IsAlreadyHit(EnemyBase* enemy) const
{
    for (auto& e : m_hitEnemies)
    {
        if (e == enemy)return true;
    }
    return false;
}

void Bullet::AddHitEnemy(EnemyBase* enemy)
{
    m_hitEnemies.push_back(enemy);
}
