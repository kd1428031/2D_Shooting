#include "EnemyBase.h"
#include "Application/Scene.h"
#include "Application/Score/ScoreManager.h"
#include "Application/TimeManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"
#include "Application/Audio/AudioManager.h"

EnemyBase::EnemyBase(Math::Vector2 pos, float scale)
    :Character(pos, scale), m_state(State::Alive), m_score(0), 
    m_shotInterval(1.0f), m_shotTimer(m_shotInterval), m_bulletOffset(30.0f), 
    m_bulletSpeed(300.0f), m_bulletScale(2.0f), m_bulletColor(1, 0, 0, 1),
    m_bulletAngle(0.0f), m_bulletAngleSpeed(300.0f), m_shotNWay(0),
    m_shotType(ShotType::Straight), m_preUpdateFlg(true)
{    
}

void EnemyBase::Draw()
{
    Math::Rectangle rect{
         (int)m_animFrame.x * m_texFrameWidth,(int)m_animFrame.y * m_texFrameHeight,
         m_texFrameWidth, m_texFrameHeight 
    };

    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex_Color(m_tex, rect, m_color);
    
    DrawImpl();
}

void EnemyBase::Update(float dt)
{
    if (m_preUpdateFlg)PreUpdate(dt);
    if (!m_preUpdateFlg)
    {
        if (m_state == State::Dying)
        {
            Death(dt);
            return;
        }

        if (m_pos.x <  SCENE.screenWidth / 2 && m_pos.x > -SCENE.screenWidth / 2 &&
            m_pos.y <  SCENE.screenHeight / 2 && m_pos.y > -SCENE.screenHeight / 2)
        {
            if (m_shotType != ShotType::None)
            {
                m_shotTimer -= dt;
                if (m_shotTimer <= 0)
                {
                    Shot(dt);
                    m_shotTimer = m_shotInterval;
                }
            }
        }
        UpdateImpl(dt);
        Move(dt);
        UpdateMatrix();
    }
}

void EnemyBase::Move(float dt)
{
    if (m_stopPos.x < m_pos.x)
    {
        m_pos += m_velocity * dt;
    }

    // 画面外で死亡
    if (m_pos.x < -SCENE.screenWidth / 2 - kDeleteMargin)
    {
        m_state = State::Dead;
    }
}

void EnemyBase::PreUpdate(float dt)
{
    m_preUpdateFlg = false;
}

void EnemyBase::Shot(float dt)
{
    switch (m_shotType)
    {
    case ShotType::None:    // 弾発射しない
        break;

    case ShotType::Straight:
        ShotStraight();
        break;

    case ShotType::NWay :
        ShotNWay();
        break;

    case ShotType::AllRange:
        ShotAllRange();
        break;
    
    case ShotType::Aimed :
        ShotAimed();
        break;

    case ShotType::Rotate:
        ShotRotate(dt);
        break;

    default:
        break;
    }
}

void EnemyBase::ShotStraight()
{
    float angle = 180.0f; // 左方向

    float rad = DirectX::XMConvertToRadians(angle);

    Math::Vector2 dir =
    {
        cos(rad),
        sin(rad)
    };

    Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
    Math::Vector2 velocity = dir * m_bulletSpeed;

    BULLETMANAGER.CreateBullet(
        BulletOwner::Enemy,
        BulletType::Normal,
        spawnPos,
        velocity,
        m_bulletScale,
        m_bulletColor
    );
    AUDIOM.PlaySeNumLimit(SoundName::kNShot);
}

void EnemyBase::ShotNWay()
{
    if (m_shotNWay <= 0) return;

    // 弾の間隔
    float angleStep = 0;
    if (m_shotNWay > 1)
    {
        angleStep = m_spreadAngle / (m_shotNWay - 1);
    }

    // 開始角（中心から左右に広げる）
    float startAngle = m_baseAngle - (m_spreadAngle / 2);

    for (int i = 0; i < m_shotNWay; i++)
    {
        float angle = startAngle + angleStep * i;
        float rad = DirectX::XMConvertToRadians(angle);

        Math::Vector2 dir =
        {
            cos(rad),
            sin(rad)
        };

        Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
        Math::Vector2 velocity = dir * m_bulletSpeed;

        BULLETMANAGER.CreateBullet(
            BulletOwner::Enemy,
            BulletType::Normal,
            spawnPos,
            velocity,
            m_bulletScale,
            m_bulletColor
        );
    }
    AUDIOM.PlaySeNumLimit(SoundName::kNShot);
}

void EnemyBase::ShotAllRange()
{
    if (m_shotAllNWay <= 0) return;

    float angleStep = 360.0f / m_shotAllNWay;

    for (int i = 0; i < m_shotAllNWay; i++)
    {
        float angle = angleStep * i;
        float rad = DirectX::XMConvertToRadians(angle);

        Math::Vector2 dir =
        {
            cos(rad),
            sin(rad)
        };

        Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
        Math::Vector2 velocity = dir * m_bulletSpeed;

        BULLETMANAGER.CreateBullet(
            BulletOwner::Enemy,
            BulletType::Normal,
            spawnPos,
            velocity,
            m_bulletScale,
            m_bulletColor
        );
    }
    AUDIOM.PlaySeNumLimit(SoundName::kNShot);
}

void EnemyBase::ShotAimed()
{
    float deg = GetAngleDeg(m_pos, PLAYERMANAGER.GetPlayer()->GetPos());
    float rad = DirectX::XMConvertToRadians(deg);

    Math::Vector2 dir =
    {
        cos(rad),
        sin(rad)
    };

    Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
    Math::Vector2 velocity = dir * m_bulletSpeed;

    BULLETMANAGER.CreateBullet(
        BulletOwner::Enemy,
        BulletType::Normal,
        spawnPos,
        velocity,
        m_bulletScale,
        m_bulletColor
    );
    AUDIOM.PlaySeNumLimit(SoundName::kNShot);
}

void EnemyBase::ShotRotate(float dt)
{
    m_bulletAngle += m_bulletAngleSpeed * dt;
    if ((int)m_bulletAngle % 45 == 0)
    {
        AUDIOM.PlaySeNumLimit(SoundName::kNShot);

    }
    if (m_bulletAngle > 360)
    {
        m_bulletAngle -= 360;
    }

    float rad = DirectX::XMConvertToRadians(m_bulletAngle);

    Math::Vector2 dir =
    {
        cos(rad),
        sin(rad)
    };

    Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
    Math::Vector2 velocity = dir * m_bulletSpeed;

    BULLETMANAGER.CreateBullet(
        BulletOwner::Enemy,
        BulletType::Normal,
        spawnPos,
        velocity,
        m_bulletScale,
        m_bulletColor
    );
}

void EnemyBase::TakeDamage(float damage)
{
    if (m_state == State::Alive)
    {
        Character::TakeDamage(damage);
        TIMEMANAGER.HitStop(kHitStopFrames);
        OnHit();
        if (m_hp <= 0)
        {
            PreDeath();
            m_state = State::Dying;
            SCOREMANAGER.AddScore(m_score);
            PLAYERMANAGER.AddDestroyCnt();
        }
    }
}