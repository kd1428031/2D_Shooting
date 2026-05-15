#include "Raven.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/ResourceManager.h"
#include "Application/Audio/AudioManager.h"

void Raven::Init()
{
    m_tex = RESOURCEMANAGER.GetTex(TexName::kRaven);

    m_scale = kScale;

    m_pos = {   PLAYERMANAGER.GetPlayer()->GetPos().x - 50.0f, 
                PLAYERMANAGER.GetPlayer()->GetPos().y + 50.0f };

    m_velocity = { 0,0 };

    m_speed = kInitSpeed;

    m_hp = kInitHp;

    m_state = State::Alive;

    m_alpha = 1.0f;

    m_animFrame = { 0, 3 };

    m_invincibleTimer = 0.0f;

    // 初回即発射のため負値で初期化
    m_shotTimer = kShotInterval;

    m_isShooting = true;

    m_angle = 0.0f;

    m_powUpFlg = false;

    m_powUpTimer = kPowUpTimerInterval;
}

void Raven::Update(float dt)
{
    UpdateShot(dt);
    UpdatePowerUp(dt);
    Move(dt);
    UpdateAnim(dt);
    UpdateMatrix();
}

void Raven::Draw()
{
    if (m_state == State::Dead) return;

    Math::Rectangle rect = {
        (int)m_animFrame.x * kTexFrameWidth,
        (int)m_animFrame.y * kTexFrameHeight, kTexFrameWidth, kTexFrameHeight
    };

    if (m_powUpFlg)
    {
        Math::Vector2 playerPos = PLAYERMANAGER.GetPlayer()->GetPos();
        Math::Color color = { 1,0,1,1 };
        SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
        SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y, playerPos.x, playerPos.y, &color);
    }

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
}

void Raven::Move(float dt)
{
    Math::Vector2 toPlayer = PLAYERMANAGER.GetPlayer()->GetPos() - m_pos;
    float dist = toPlayer.Length();
    toPlayer.Normalize();

    float minDist = 45.0f;
    float maxDist = 55.0f;

    if (dist > maxDist)
    {
        m_velocity = toPlayer * m_speed;
    }
    else if (dist < minDist)
    {
        m_velocity = -toPlayer * m_speed;
    }
    else
    {
        m_velocity = { 0,0 };
    }

    m_pos += m_velocity * dt;
}

void Raven::UpdateAnim(float dt)
{
    m_animFrame.x += m_animSpeed * dt;

    if (m_animFrame.x > 3)
    {
        m_animFrame.x = 0;
    }
}

void Raven::UpdateShot(float dt)
{
    if (PLAYERMANAGER.GetPlayer()->GetActionFlg())
    {
        m_shotTimer -= dt;

        if (m_isShooting)
        {
            if (m_shotTimer <= 0.0f)
            {
                AUDIOM.PlaySeNumLimit(SoundName::kNShot);

                float rate = 1.0f;
                if (m_powUpFlg)
                {
                    rate = 0.33f;
                    ShotNWay(5);
                }
                else
                {
                    rate = 1.0f;
                    Shot(dt);
                }
                m_shotTimer = kShotInterval * rate;
            }
        }
    }
}

void Raven::UpdatePowerUp(float dt)
{
    if (m_powUpFlg)
    {
        if (m_powUpTimer > 0.0f)
        {
            m_powUpTimer -= 10 * dt;
            PLAYERMANAGER.GetPlayer()->SetMp(PLAYERMANAGER.GetPlayer()->GetMp() - 10 * dt);
            m_color = { 1,0,0,1 };
        }
        if (m_powUpTimer <= 0.0f || PLAYERMANAGER.GetPlayer()->GetMp() <= 0)
        {
            m_powUpFlg = false;
            m_powUpTimer = kPowUpTimerInterval;
            m_color = { 1,1,1,1 };
        }
    }
    else
    {
        m_powUpTimer = kPowUpTimerInterval;
        m_color = { 1,1,1,1 };
    }
}

void Raven::Shot(float dt)
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(kBulletOffsetX, 0);
    Math::Vector2 dir = { 1, 0 };
    BULLETMANAGER.CreateBullet(BulletOwner::Player, BulletType::Normal, spawnPos, dir * kBulletSpeed, kBulletScale, kBulletColor);
}

void Raven::ShotNWay(int num)
{
    if (num <= 0) return;

    // 弾の間隔
    float angleStep = 0;
    if (num > 1)
    {
        angleStep = m_spreadAngle / (num - 1);
    }

    // 開始角（中心から左右に広げる）
    float startAngle = m_baseAngle - (m_spreadAngle / 2);

    for (int i = 0; i < num; i++)
    {
        float angle = startAngle + angleStep * i;
        float rad = DirectX::XMConvertToRadians(angle);

        Math::Vector2 dir =
        {
            cos(rad),
            sin(rad)
        };

        Math::Vector2 spawnPos = m_pos + dir * kBulletOffsetX;
        Math::Vector2 velocity = dir * kBulletSpeed;

        BULLETMANAGER.CreateBullet(
            BulletOwner::Player,
            BulletType::Normal,
            spawnPos,
            velocity,
            kBulletScale,
            kBulletColor
        );
    }
}

void Raven::Death(float dt)
{
    m_alpha -= dt;
    if (m_alpha <= 0)m_state = State::Dead;
}
