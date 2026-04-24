#include "Player.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"
#include "Application/Input/InputManager.h";

void Player::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kPlayer);

    m_pos = { kInitPosX, kInitPosY };
    
    m_velocity = { 0,0 };

    m_speed = kInitSpeed;

    m_hp = kInitHp;
    
    m_state = State::Alive;

    m_alpha = 1.0f;

    m_animFrame = {};
    
    m_invincibleTimer = 0.0f;

    // ‰‰ñ‘¦”­ŽË‚Ì‚½‚ß•‰’l‚Å‰Šú‰»
    m_shotTimer = -1.0f;

    // ‰Šúó‘Ô‚Í’Êí’e
    m_shotType = ShotType::NormalShot;

    m_isShooting = false;

    m_angle = 0.0f;
}

void Player::Update(float dt)
{
    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }
    
    Move(dt);

    // ’e”­ŽËˆ—
    Shot(dt);
  
    UpdateInvincible(dt);
    UpdateAnim(dt);
    UpdateMatrix();
}

void Player::Draw()
{
    if (m_state == State::Dead) return;

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ (int)m_animFrame.x * kTexFrameSize, 0, kTexFrameSize, kTexFrameSize }, m_alpha);
}

void Player::Move(float dt)
{
    m_velocity = { 0.0f, 0.0f };

    // ’á‘¬E‚‘¬Ø‚è‘Ö‚¦
    if(INPUT.IsKeyHeld(VK_SHIFT))
    {
        m_speed = kLowSpeed;
    }
    else
    {
        m_speed = kHighSpeed;
    }

    // ˆÚ“®ˆ—(‹t•ûŒü‚ð“¯Žž‰Ÿ‚µ‚µ‚½‚ç’âŽ~‚·‚é‚æ‚¤‚É)
    bool up     = INPUT.IsKeyHeld(VK_UP)    || INPUT.IsKeyHeld('W');
    bool down   = INPUT.IsKeyHeld(VK_DOWN)  || INPUT.IsKeyHeld('S');
    bool left   = INPUT.IsKeyHeld(VK_LEFT)  || INPUT.IsKeyHeld('A');
    bool right  = INPUT.IsKeyHeld(VK_RIGHT) || INPUT.IsKeyHeld('D');

    if (up    && !down)  m_velocity.y = m_speed;
    if (down  && !up)    m_velocity.y = -m_speed;
    if (left  && !right) m_velocity.x = -m_speed;
    if (right && !left)  m_velocity.x = m_speed;

    m_pos += m_velocity * dt;

    // ˆÚ“®§ŒÀ
    if (m_pos.x >= SCENE.screenWidth - kRadius)m_pos.x = SCENE.screenWidth - kRadius;
    if (m_pos.x <= -SCENE.screenWidth + kRadius)m_pos.x = -SCENE.screenWidth + kRadius;
    if (m_pos.y >= SCENE.screenHeight - kRadius)m_pos.y = SCENE.screenHeight - kRadius;
    if (m_pos.y <= -SCENE.screenHeight + kRadius)m_pos.y = -SCENE.screenHeight + kRadius;
}

void Player::UpdateAnim(float dt)
{
    m_blinkTimer -= dt;

    if (m_blinkTimer <= 0.0f)
    {
        m_animFrame.x += m_animSpeed * dt;

        if (m_animFrame.x >= kMaxAnimFrame)
        {
            m_animFrame.x = kMaxAnimFrame;
            m_animSpeed = -kAnimSpeed;
        }
        if (m_animFrame.x <= 0.0f)
        {
            m_animFrame.x = 0.0f;
            m_animSpeed = kAnimSpeed;
            m_blinkTimer = kBlinkInterval;
        }
    }
}

void Player::UpdateInvincible(float dt)
{
    if (m_state == State::Invincible)
    {
        m_invincibleTimer -= dt;
        m_alpha = 0.5f;

        if (m_invincibleTimer <= 0.0f)
        {
            m_state = State::Alive;
            m_alpha = 1.0f;
        }
    }
}

void Player::Shot(float dt)
{
    // ’e”­ŽË
    m_isShooting = INPUT.IsKeyHeld(VK_SPACE);

    // ’e”­ŽËŠÔŠuˆ—
    m_shotTimer -= dt;

    if (m_isShooting)
    {
        if (m_shotTimer <= 0.0f)
        {
            // ”­ŽËŠÔŠuƒ^ƒCƒ}[ƒŠƒZƒbƒg
            m_shotTimer = kShotInterval;

            // ’e‚ÌŽí—Þ
            switch (m_shotType)
            {
            case ShotType::NormalShot: NormalShot(); break;
            case ShotType::PenetratShot: PenetratShot(); break;
            default:break;
            }
        }
    }
}

void Player::NormalShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    BULLETMANAGER.CreateBullet(BulletType::Normal, spawnPos, Math::Vector2(kBulletSpeed, 0), kBulletScale, kBulletColor);
}

void Player::PenetratShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    BULLETMANAGER.CreateBullet(BulletType::Penetrat, spawnPos, Math::Vector2(kBulletSpeed, 0), kBulletScale, kBulletColor);
}

void Player::TakeDamage(float damage)
{
    if (m_state != State::Invincible)
    {
        m_invincibleTimer = kInvincibleTime;
        m_state = State::Invincible;

        Character::TakeDamage(damage);
        if (m_hp <= 0) m_state = State::Dying;
    }
}

void Player::Death(float dt)
{
    m_state = State::Dead;
}