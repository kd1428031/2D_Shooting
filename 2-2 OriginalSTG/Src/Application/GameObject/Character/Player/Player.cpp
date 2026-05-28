#include "Player.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/Scene.h"
#include "Application/ResourceManager.h"
#include "Application/Input/InputManager.h"
#include "Application/TimeManager.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Effect/MpMax/MpMax.h"
#include "Application/Random/Random.h"
#include "Application/Audio/AudioManager.h"
#include "Application/Ui/UiManager.h"
#include "Application/Ui/BomdWaitCounter.h"
#include "Application/Ui/RavenWaitCounter.h"

Player::~Player()
{
    if (m_magicCircle)
    {
        m_magicCircle->SetOwner(nullptr);
        m_magicCircle->Kill();
        m_magicCircle = nullptr;
    }
}

void Player::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kPlayer);
    m_heartTex = RESOURCEMANAGER.GetTex(TexName::kHeart);
    m_cntTex = RESOURCEMANAGER.GetTex(TexName::kNumber);
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

    // ‰‰ñ‘¦”­ŽË‚Ì‚½‚ß•‰’l‚Å‰Šú‰»
    m_shotTimer = -1.0f;

    // ‰Šúó‘Ô‚Í’Êí’e
    m_shotType = ShotType::NormalShot;

    m_bombType = BombType::Lightning;

    m_bomdTimer = 0.0f;

    m_isShooting = false;

    m_angle = 0.0f;

    m_uiAlpha = 1.0f;

    m_uiHeartAlpha = 1.0f;

    m_lowFlg = false;
}

void Player::Update(float dt)
{
    if (m_state == State::Dead) return;

    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }

    // ŠO•”‚Åíœ‚³‚ê‚½ê‡‚ÌˆÀ‘Sô
    if (m_magicCircle && !m_magicCircle->IsAlive())
    {
        m_magicCircle = nullptr;
    }
    
    if (m_mp < kInitMp) m_mp += m_mpRegen;

    if (m_actionFlg)
    {
        Move(dt);

        // ’e”­ŽËˆ—
        Shot(dt);

        Bomb(dt);
        RavenBomb(dt);
    }

    auto raven = PLAYERMANAGER.GetRaven();
    if (raven) 
    {
        if (PLAYERMANAGER.GetRaven()->GetPowUpFlg())
        {
            m_uiAlpha += m_uiAlphaBlink * dt;
            if (m_uiAlpha <= 0.5f || m_uiAlpha >= 1.0f)
            {
                m_uiAlphaBlink *= -1;
            }
        }
        else
        {
            m_uiAlpha = 1.0f;
        }
    }

    if (m_state == State::Invincible)
    {
        m_uiHeartAlpha += m_uiHeartAlphaBlink * dt;
        if (m_uiHeartAlpha <= 0.5f || m_uiHeartAlpha >= 1.0f)
        {
            m_uiHeartAlphaBlink *= -1;
        }
    }
    else
    {
        m_uiHeartAlpha = 1.0f;
    }

    if (m_mp <= 0)m_mp = 0;
    m_isHit = false;
    UpdateInvincible(dt);
    UpdateAnim(dt);
    UpdateMatrix();
    Math::Vector2 pos = { -550.0f,-300.0f };
    m_heartMat = CreateMatrix(pos, { 3, 3 }, 0);
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
    auto raven = PLAYERMANAGER.GetRaven();
    if (raven->GetPowUpTimer() > 0 && raven->GetPowUpFlg())
    {
        int digits = 2;

        for (int i = 0; i < digits; i++)
        {
            int digitIndex = ((int)raven->GetPowUpTimer() / (int)pow(10, digits - 1 - i)) % 10;
            float srcX = 128 * digitIndex;

            Math::Rectangle rect{
                (int)srcX, 0, 128, 128
            };
            Math::Vector2 ravenPos = raven->GetPos();
            Math::Vector2 pos = { ravenPos.x + (float)(i * (128 + -115)) - 10, ravenPos.y + 40 };
            Math::Vector2 size = { 0.25f, 0.25f };
            m_cntMat = CreateMatrix(pos, size, 0);
            SHADER.m_spriteShader.SetMatrix(m_cntMat);
            SHADER.m_spriteShader.DrawTex_Color(m_cntTex, rect, Math::Color(0.8f, 0.2f, 0.8f, 1.0f));
        }
    }

    Math::Rectangle heartRect = {}; 
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
    SHADER.m_spriteShader.DrawTex(m_heartTex, heartRect, m_uiHeartAlpha);

    Math::Color backColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    Math::Color gaugeColor;
    if (!PLAYERMANAGER.GetRaven()->GetPowUpFlg())
    {
        gaugeColor = { 0.8f, 0.2f, 0.8f, m_uiAlpha };
    }
    else
    {
        gaugeColor = { 0.9f, 0.4f, 0.9f, m_uiAlpha };
    }
    float width = 100.0f;
    float mpBar = (m_mp / kInitMp) * width;
    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    SHADER.m_spriteShader.DrawBox(-450 + width, -300, 105, 15, &backColor, true);
    SHADER.m_spriteShader.DrawBox(-450 + mpBar, -300, mpBar, 10, &gaugeColor, true);
}

void Player::Move(float dt)
{
    m_velocity = { 0.0f, 0.0f };

    // ’á‘¬E‚‘¬Ø‚è‘Ö‚¦
    if(INPUT.IsKeyTriggered(VK_SHIFT))
    {
        m_lowFlg = !m_lowFlg;
    }
    if (m_lowFlg && m_mp >= kInitMp)
    {
        m_lowFlg = false;

        if (m_magicCircle)
        {
            MpMax* mpMax = static_cast<MpMax*>(EFFCTMANAGER.CreateEffect(EffectType::MpMax, m_pos, 1));
            mpMax->SetOwner(this);
            AUDIOM.PlaySe(SoundName::kMpMax);
        }
    }

    if (m_lowFlg)
    {
        m_speed = kLowSpeed;
        m_mpRegen = 15.0f * dt;
        m_shotType = ShotType::PenetratShot;
        if (!m_magicCircle)
        {
            m_magicCircle = EFFCTMANAGER.CreateEffect(EffectType::MagicCircle, m_pos, 0.75f);
            m_magicCircle->SetOwner(this);
        }
    }
    else
    {
        m_speed = kHighSpeed;
        m_mpRegen = 5.0f * dt;
        m_shotType = ShotType::NormalShot;
        if (m_magicCircle)
        {
            m_magicCircle->Kill();
            m_magicCircle = nullptr;
        }
    }

    // ˆÚ“®ˆ—(‹t•ûŒü‚ð“¯Žž‰Ÿ‚µ‚µ‚½‚ç’âŽ~‚·‚é‚æ‚¤‚É)
    bool up     = INPUT.IsKeyHeld(VK_UP)  ;
    bool down   = INPUT.IsKeyHeld(VK_DOWN);
    bool left   = INPUT.IsKeyHeld(VK_LEFT);
    bool right  = INPUT.IsKeyHeld(VK_RIGHT);

    Math::Vector2 dir;

    if (up    && !down)  dir.y = 1;
    if (down  && !up)    dir.y = -1;
    if (left  && !right) dir.x = -1;
    if (right && !left)  dir.x = 1;

    if(dir.Length() > 0.0f)dir.Normalize();

    m_velocity = m_speed * dir;
    m_pos += m_velocity * dt;

    // ˆÚ“®§ŒÀ
    if (m_pos.x >=  SCENE.GetScreenWidth() /2  - kRadius)m_pos.x =  SCENE.GetScreenWidth() /2  - kRadius;
    if (m_pos.x <= -SCENE.GetScreenWidth() /2  + kRadius)m_pos.x = -SCENE.GetScreenWidth() /2  + kRadius;
    if (m_pos.y >=  SCENE.GetScreenHeight()/2 - kRadius)m_pos.y =  SCENE.GetScreenHeight()/2 - kRadius;
    if (m_pos.y <= -SCENE.GetScreenHeight()/2 + kRadius+80)m_pos.y = -SCENE.GetScreenHeight()/2 + kRadius+80;
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
    m_isShooting = INPUT.IsKeyHeld('Z');

    // ’e”­ŽËŠÔŠuˆ—
    m_shotTimer -= dt;

    if (m_isShooting)
    {
        if (m_shotTimer <= 0.0f)
        {
            // ”­ŽËŠÔŠuƒ^ƒCƒ}[ƒŠƒZƒbƒg
            m_shotTimer = kShotInterval;

            // MPÁ”ï
            //m_mp -= 1;

            AUDIOM.PlaySeNumLimit(SoundName::kNShot);        

            // ’e‚ÌŽí—Þ
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
    BULLETMANAGER.CreateBullet(BulletOwner::Player, BulletType::Normal, BulletColor::Violet, spawnPos, dir * kBulletSpeed, kBulletScale);
}

void Player::PenetratShot()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    Math::Vector2 dir = { 1, 0 };
    BULLETMANAGER.CreateBullet(BulletOwner::Player, BulletType::Penetrat, BulletColor::None, spawnPos, dir * kBulletSpeed, kBulletScale);
}

void Player::Bomb(float dt)
{
    m_isBomd = INPUT.IsKeyTriggered('X');

    m_bomdTimer -= 10 * dt;
    if (m_bomdTimer <= 0)m_bomdTimer = 0;

    if (m_isBomd)
    {
        if (m_bomdTimer <= 0 && m_mp >= 80)
        {
            if (m_bombType == BombType::Lightning)
            {
                m_mp -= 80;
                m_bomdTimer = kBomdInterval;

                m_invincibleTimer = kInvincibleTime;
                m_state = State::Invincible;

                Lightning();

                for (int i = 0; i < 3; i++)
                {
                    AUDIOM.PlaySeNumLimit(SoundName::kLighting);
                }
            }
        }
        // Žg‚¦‚È‚¢Žž
        else
        {
            BomdWaitCounter* bomd = static_cast<BomdWaitCounter*>(UIMANAGER.GetUi(UiType::BomdWaitCounter));
            bomd->Shake();
            AUDIOM.PlaySeNumLimit(SoundName::kError);
        }
    }
}

void Player::RavenBomb(float dt)
{
    m_isRavenBomd = INPUT.IsKeyTriggered('C');

    auto raven = PLAYERMANAGER.GetRaven();

    if (!raven->GetPowUpFlg())
    {
        m_ravenBomdTimer -= 10 * dt;
    }
    if (m_ravenBomdTimer <= 0)m_ravenBomdTimer = 0;


    if (m_isRavenBomd)
    {
        if (m_ravenBomdTimer <= 0 && m_mp >= 40 && !raven->GetPowUpFlg())
        {
            m_mp -= 40;

            m_ravenBomdTimer = kRavenBomdInterval;

            raven->SetPowUpFlg(true);

            EFFCTMANAGER.CreateEffect(EffectType::SoulLinkText, { 0, 0 }, 1);
        }
        // Žg‚¦‚È‚¢Žž
        else
        {
            RavenWaitCounter* bomd = static_cast<RavenWaitCounter*>(UIMANAGER.GetUi(UiType::RavenBomdWaitCounter));
            bomd->Shake();
            AUDIOM.PlaySeNumLimit(SoundName::kError);
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

void Player::Heal(int healValue)
{
    m_hp += healValue;
    if (m_hp >= kInitHp)m_hp = kInitHp;
}

void Player::TakeDamage(float damage)
{
    if (m_state == State::Dying || m_state == State::Dead)return;

    if (m_state != State::Invincible)
    {
        m_invincibleTimer = kInvincibleTime;
        m_state = State::Invincible;

        TIMEMANAGER.HitStop(5);
        EFFCTMANAGER.CreateEffect(EffectType::HitEffect, m_pos, 0.15f);
        AUDIOM.PlaySe(SoundName::kHit);
        AUDIOM.PlaySe(SoundName::kRing);
        Character::TakeDamage(damage);
        if (m_hp <= 0) m_state = State::Dying;
        m_isHit = true;
        TIMEMANAGER.HitStop(kHitStopFrames);
    }
}

void Player::Death(float dt)
{
    m_alpha -= dt;
    if(m_alpha<=0)m_state = State::Dead;
}