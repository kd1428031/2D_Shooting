#include "Bullet.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

Bullet::Bullet(BulletOwner owner, BulletType type, BulletColor color, Math::Vector2 pos, Math::Vector2 velocity, float scale)
    : GameObject(pos, scale), m_owner(owner), m_type(type), m_isAlive(true),
    m_lifeTimer(kLifeTimer),m_spinAngle(0.0f)
{
    m_radius = kRadius;
    m_velocity = velocity;
    m_color = { 1.0f,1.0f,1.0f,1.0f };

    switch (type)
    {
    case BulletType::Normal:    InitNormalBullet();     break;
    case BulletType::Penetrat:  InitPenetratBullet();   break;
    case BulletType::Rotate:    InitRotateBullet();     break;
    default:break;
    }

    switch (color)
    {
    case BulletColor::None:
        break;
    case BulletColor::Violet:
        m_tex = RESOURCEMANAGER.GetTex(TexName::kVioletBullet);
        break;
    case BulletColor::Red:
        m_tex = RESOURCEMANAGER.GetTex(TexName::kRedBullet);
        break;
    case BulletColor::Black:
        m_tex = RESOURCEMANAGER.GetTex(TexName::kBlackBullet);
        break;
    case BulletColor::Crow:
        m_tex = RESOURCEMANAGER.GetTex(TexName::kCrowBullet);
        break;
    }
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
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

    Math::Rectangle rect{ m_texOffsetX, m_texOffsetY, kTexFrameWidth, kTexFrameHeight };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void Bullet::Move(float dt)
{
    if (m_type == BulletType::Rotate)
    {
        UpdateRotate(dt);
    }

    m_pos += m_velocity * dt;

    // 画面外チェック
    if (m_pos.x > SCENE.GetScreenWidth() /2 + kDeleteMargin || m_pos.y > SCENE.GetScreenHeight() /2 + kDeleteMargin ||
        m_pos.x < -SCENE.GetScreenWidth() /2 - kDeleteMargin || m_pos.y < -SCENE.GetScreenHeight() /2 - kDeleteMargin)
    {
        Destroy();
    }
}

void Bullet::UpdateRotate(float dt)
{
    m_spinAngle += kSpinAngleSpeed * dt;
    if (m_spinAngle > 360)
    {
        m_spinAngle -= 360;
    }

    m_velocity.x = cos(DirectX::XMConvertToRadians(m_spinAngle)) * kRotateSpeed;
    m_velocity.y = sin(DirectX::XMConvertToRadians(m_spinAngle)) * kRotateSpeed;
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

void Bullet::InitNormalBullet()
{
    if (m_owner == BulletOwner::Player)
    {
        m_texOffsetX = kTexNormalOffsetX;
        m_texOffsetY = kTexNormalOffsetY;
    }
    else if (m_owner == BulletOwner::Enemy)
    {
        m_texOffsetX = 0;
        m_texOffsetY = 0;
    }
    m_damage = kNormalDamage;
}

void Bullet::InitPenetratBullet()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kPenetratBullet);
    m_texOffsetX = 0;
    m_texOffsetY = kPenetrateTexOffsetY;
    m_damage = kPenetrateDamage;
    m_color = { 0.8f,0.2f,0.8f,1.0f };
}

void Bullet::InitRotateBullet()
{
    m_texOffsetY = kTexNormalOffsetY;
    m_damage = kNormalDamage;
}
