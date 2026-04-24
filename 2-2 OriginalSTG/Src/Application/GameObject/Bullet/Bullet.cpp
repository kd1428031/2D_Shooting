#include "Bullet.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Bullet::Bullet(BulletOwner owner, BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale, Math::Color color)
    : GameObject(pos, scale), m_owner(owner), m_type(type), m_isAlive(true),
    m_lifeTimer(kLifeTimer),m_damage(1),m_spinAngle(0.0f)
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

    m_lifeTimer -= dt;
    if (m_lifeTimer <= 0)m_isAlive = false;
}

void Bullet::Draw()
{
    if (!m_isAlive) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, Math::Rectangle{ 0, kTexOffsetY, kTexFrameSize, kTexFrameSize }, m_color);
}

void Bullet::Move(float dt)
{
    if (m_type == BulletType::Rotate)
    {
        UpdateRotate(dt);
    }

    m_pos += m_velocity * dt;

    // 画面外チェック
    if (m_pos.x > SCENE.screenWidth + kDeleteMargin || m_pos.y > SCENE.screenHeight + kDeleteMargin ||
        m_pos.x < -SCENE.screenWidth - kDeleteMargin || m_pos.y < -SCENE.screenHeight - kDeleteMargin)
    {
        m_isAlive = false;
    }
}

void Bullet::UpdateRotate(float dt)
{
    m_spinAngle += 300 * dt;
    if (m_spinAngle > 360)
    {
        m_spinAngle -= 360;
    }

    m_velocity.x = cos(DirectX::XMConvertToRadians(m_spinAngle)) * 300;
    m_velocity.y = sin(DirectX::XMConvertToRadians(m_spinAngle)) * 300;
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
