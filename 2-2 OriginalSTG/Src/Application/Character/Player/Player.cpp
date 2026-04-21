#include "Player.h"
#include "Application/Bullet/BulletManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"

void Player::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kPlayer);

    m_pos = { kInitPosX, kInitPosY };
    
    m_velocity = { 0,0 };

    m_hp = kInitHp;
    
    m_state = State::Alive;

    m_animFrame = {};
    
    m_invincibleTimer = 0.0f;

    // èââÒë¶î≠éÀÇÃÇΩÇﬂïâílÇ≈èâä˙âª
    m_shotTimer = -1.0f;

    // èâä˙èÛë‘ÇÕí èÌíe
    m_shotType = ShotType::NormalShot;

    m_isShooting = false;
}

void Player::Update(float dt)
{
    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }
    
    Move(dt);

    // íeî≠éÀèàóù
    Shot(dt);

    // ñ≥ìGéûä‘èàóù
    if (m_invincibleTimer > 0.0f)
    {
        m_invincibleTimer -= dt;
    }

    UpdateAnim(dt);
    UpdateMatrix();
}

void Player::Draw()
{
    if (m_state == State::Dead) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ (int)m_animFrame.x * kTexFrameSize, 0, kTexFrameSize, kTexFrameSize }, 1.0f);
}

void Player::Move(float dt)
{
    m_velocity = { 0.0f, 0.0f };

    // à⁄ìÆèàóù
    if (GetAsyncKeyState(VK_UP) & 0x8000) m_velocity.y = kInitSpeed;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) m_velocity.y = -kInitSpeed;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) m_velocity.x = -kInitSpeed;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) m_velocity.x = kInitSpeed;

    m_pos += m_velocity * dt;

    // à⁄ìÆêßå¿
    if (m_pos.x >= SCENE.screenWidth - kRadius)m_pos.x = SCENE.screenWidth - kRadius;
    if (m_pos.x <= -SCENE.screenWidth + kRadius)m_pos.x = -SCENE.screenWidth + kRadius;
    if (m_pos.y >= SCENE.screenHeight - kRadius)m_pos.y = SCENE.screenHeight - kRadius;
    if (m_pos.y <= -SCENE.screenHeight + kRadius)m_pos.y = -SCENE.screenHeight + kRadius;
}

void Player::UpdateMatrix()
{
    m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
    m_rotMat = Math::Matrix::CreateRotationZ(m_angle);
    m_scaleMat = Math::Matrix::CreateScale(m_scale, m_scale, 1);
    m_mat = m_scaleMat * m_rotMat * m_transMat;
}

void Player::UpdateAnim(float dt)
{
    // ÉAÉjÉÅÅ[ÉVÉáÉì
    m_animFrame.x += kAnimSpeed * dt;
    if (m_animFrame.x > kMaxAnimFrame)
    {
        m_animFrame.x = 0;
    }
}

void Player::Shot(float dt)
{
    // íeî≠éÀ
    m_isShooting = GetAsyncKeyState('Z') & 0x8000;

    // íeî≠éÀä‘äuèàóù
    m_shotTimer -= dt;

    if (m_isShooting)
    {
        if (m_shotTimer <= 0.0f)
        {
            // î≠éÀä‘äuÉ^ÉCÉ}Å[ÉäÉZÉbÉg
            m_shotTimer = kShotInterval;

            // íeÇÃéÌóﬁ
            switch (m_shotType)
            {
            case ShotType::NormalShot: NormalShot(); break;
            default:break;
            }
        }
    }
}

void Player::NormalShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    BULLETMANAGER.CreateBullet(spawnPos, Math::Vector2(kBulletSpeed, 0), kBulletScale, Math::Color(1, 0, 0, 1));
}

void Player::TakeDamage(float damage)
{
    if (m_invincibleTimer <= 0)
    {
        m_invincibleTimer = kInvincibleTime;
        Character::TakeDamage(damage);
        if (m_hp <= 0) m_state = State::Dying;
    }
}

void Player::Death(float dt)
{

}