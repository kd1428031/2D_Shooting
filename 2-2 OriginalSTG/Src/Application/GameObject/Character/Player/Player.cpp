#include "Player.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"
#include "Application/Input/InputManager.h"
#include "Application/TimeManager.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Random/Random.h"

void Player::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kPlayer);
    m_heartTex = RESOURCEMANAGER.GetTex(TexName::kHeart);

    m_scale = kScale;

    m_pos = { kInitPosX, kInitPosY };
    
    m_velocity = { 0,0 };

    m_speed = kInitSpeed;

    m_hp = kInitHp;

    m_mp = kInitMp;
    
    m_state = State::Alive;

    m_alpha = 1.0f;

    m_animFrame = {};
    
    m_actionFlg = true;

    m_invincibleTimer = 0.0f;

    // èââÒë¶î≠éÀÇÃÇΩÇﬂïâílÇ≈èâä˙âª
    m_shotTimer = -1.0f;

    // èâä˙èÛë‘ÇÕí èÌíe
    m_shotType = ShotType::NormalShot;

    m_bombType = BombType::Lightning;

    m_bomdTimer = 0.0f;

    m_isShooting = false;

    m_angle = 0.0f;

    m_uiAlpha = 1.0f;
}

void Player::Update(float dt)
{
    if (m_state == State::Dead) return;

    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }
    
    if (m_mp < kInitMp) m_mp += m_mpRegen;

    if (m_actionFlg)
    {
        Move(dt);

        // íeî≠éÀèàóù
        if (m_mp > 1)
        {
            Shot(dt);
        }

        Bomb(dt);
    }

    if (m_mp <= 0)m_mp = 0;

    UpdateInvincible(dt);
    UpdateAnim(dt);
    UpdateMatrix();
    Math::Vector2 pos = { -500.0f,-250.0f };
    m_heartMat = CreateMatrix(pos, { 4, 4 }, 0);
}

void Player::Draw()
{
    if (m_state == State::Dead) return;

    Math::Rectangle rect = { 
        (int)m_animFrame.x * kTexFrameWidth, 0, kTexFrameWidth, kTexFrameHeight 
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, rect, m_alpha);
}

void Player::DrawUi()
{
    Math::Rectangle heartRect;
    switch (m_hp)
    {
    case 3:
        heartRect = { 33, 11 * 0, 33, 11 };
        break;
    case 2:
        heartRect = { 33, 11 * 2, 33, 11 };
        break;
    case 1:
        heartRect = { 33, 11 * 4, 33, 11 };
        break;
    case 0:
        heartRect = { 33, 11 * 6, 33, 11 };
        break;
    }

    SHADER.m_spriteShader.SetMatrix(m_heartMat);
    SHADER.m_spriteShader.DrawTex(m_heartTex, heartRect, m_uiAlpha);


    Math::Color backColor = { 0.0f, 0.0f, 0.0f, m_uiAlpha };
    Math::Color gaugeColor = { 0.8f, 0.2f, 0.8f, m_uiAlpha };
    float width = 100.0f;
    float mpBar = (m_mp / kInitMp) * width;
    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    SHADER.m_spriteShader.DrawBox(-600 + width, -300, 105, 15, &backColor, true);
    SHADER.m_spriteShader.DrawBox(-600 + mpBar, -300, mpBar, 10, &gaugeColor, true);
}

void Player::Move(float dt)
{
    m_velocity = { 0.0f, 0.0f };

    // í·ë¨ÅEçÇë¨êÿÇËë÷Ç¶
    if(INPUT.IsKeyHeld(VK_SHIFT))
    {
        m_speed = kLowSpeed;
        m_mpRegen = 25.0f * dt;
        m_shotType = ShotType::PenetratShot;
    }
    else
    {
        m_speed = kHighSpeed;
        m_mpRegen = 5.0f * dt;
        m_shotType = ShotType::NormalShot;
    }

    // à⁄ìÆèàóù(ãtï˚å¸ÇìØéûâüÇµÇµÇΩÇÁí‚é~Ç∑ÇÈÇÊÇ§Ç…)
    bool up     = INPUT.IsKeyHeld(VK_UP)    || INPUT.IsKeyHeld('W');
    bool down   = INPUT.IsKeyHeld(VK_DOWN)  || INPUT.IsKeyHeld('S');
    bool left   = INPUT.IsKeyHeld(VK_LEFT)  || INPUT.IsKeyHeld('A');
    bool right  = INPUT.IsKeyHeld(VK_RIGHT) || INPUT.IsKeyHeld('D');

    Math::Vector2 dir;

    if (up    && !down)  dir.y = 1;
    if (down  && !up)    dir.y = -1;
    if (left  && !right) dir.x = -1;
    if (right && !left)  dir.x = 1;

    if(dir.Length() > 0.0f)dir.Normalize();

    m_velocity = m_speed * dir;
    m_pos += m_velocity * dt;

    // à⁄ìÆêßå¿
    if (m_pos.x >=  SCENE.screenWidth/2  - kRadius)m_pos.x =  SCENE.screenWidth/2  - kRadius;
    if (m_pos.x <= -SCENE.screenWidth/2  + kRadius)m_pos.x = -SCENE.screenWidth/2  + kRadius;
    if (m_pos.y >=  SCENE.screenHeight/2 - kRadius)m_pos.y =  SCENE.screenHeight/2 - kRadius;
    if (m_pos.y <= -SCENE.screenHeight/2 + kRadius)m_pos.y = -SCENE.screenHeight/2 + kRadius;
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
    // íeî≠éÀ
    m_isShooting = INPUT.IsKeyHeld('Z') || INPUT.IsLeftClick();

    // íeî≠éÀä‘äuèàóù
    m_shotTimer -= dt;

    if (m_isShooting)
    {
        if (m_shotTimer <= 0.0f)
        {
            // î≠éÀä‘äuÉ^ÉCÉ}Å[ÉäÉZÉbÉg
            m_shotTimer = kShotInterval;

            // MPè¡îÔ
            m_mp -= 1;

            // íeÇÃéÌóﬁ
            switch (m_shotType)
            {
            case ShotType::NormalShot:   NormalShot();   break;
            case ShotType::PenetratShot: PenetratShot(); break;
            default:break;
            }
        }
    }
}

void Player::NormalShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    Math::Vector2 dir = { 1, 0 };
    BULLETMANAGER.CreateBullet(BulletOwner::Player, BulletType::Normal, spawnPos, dir * kBulletSpeed, kBulletScale, kBulletColor);
}

void Player::PenetratShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    Math::Vector2 dir = { 1, 0 };
    BULLETMANAGER.CreateBullet(BulletOwner::Player, BulletType::Penetrat, spawnPos, dir * kBulletSpeed, kBulletScale, kBulletColor);
}

void Player::Bomb(float dt)
{
    m_isBomd = INPUT.IsKeyHeld('X') || INPUT.IsRightClick();

    m_bomdTimer -= 10 * dt;
    if (m_bomdTimer <= 0)m_bomdTimer = 0;

    if (m_isBomd)
    {
        if (m_bomdTimer <= 0)
        {
            if (m_bombType == BombType::Lightning)
            {
                if (m_mp >= 80)
                {
                    m_mp -= 0;
                    m_bomdTimer = kBomdInterval;

                    m_invincibleTimer = kInvincibleTime;
                    m_state = State::Invincible;

                    Lightning();
                }
            }
        }
    }
}

void Player::Lightning()
{
    for (int i = 0; i < Random::Range(20, 40); i++)
    {
        EFFCTMANAGER.CreateEffect(EffectType::Lightning,
            { 0 + Random::Range(-700.0f, 700.0f), Random::Range(40.0f, 100.0f) }, 8);
    }
    EFFCTMANAGER.CreateEffect(EffectType::LightningText, { 0, 0 }, 1);
}

void Player::TakeDamage(float damage)
{
    if (m_state == State::Dying || m_state == State::Dead)return;

    if (m_state != State::Invincible)
    {
        m_invincibleTimer = kInvincibleTime;
        m_state = State::Invincible;

        if (m_hp <= 1)return;

        Character::TakeDamage(damage);
        if (m_hp <= 0) m_state = State::Dying;

        TIMEMANAGER.HitStop(kHitStopFrames);
    }
}

void Player::Death(float dt)
{
    m_alpha -= dt;
    //m_uiAlpha -= dt;
    if(m_alpha<=0)m_state = State::Dead;
}