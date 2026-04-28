#include "EnemyBase.h"
#include "Application/Scene.h"
#include "Application/Score/ScoreManager.h"
#include "Application/TimeManager.h"
#include "Application/GameObject/Bullet/BulletManager.h"
#include "Application/GameObject/Character/Player/PlayerManager.h"

EnemyBase::EnemyBase(Math::Vector2 pos, float scale)
    :Character(pos, scale), m_state(State::Alive), m_score(0), m_shotTimer(0.0f),
    m_shotInterval(1.0f), m_bulletOffset(30.0f), m_bulletSpeed(300.0f), 
    m_bulletScale(2.0f), m_bulletColor(1, 0, 0, 1),
    m_bulletAngle(0.0f), m_bulletAngleSpeed(300.0f)
{    
}

void EnemyBase::Draw()
{
    if (m_state == State::Dead) return;
    SHADER.m_spriteShader.SetMatrix(m_mat);
    SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle{ (int)m_animFrame.x * m_texFrameWidth,(int)m_animFrame.y * m_texFrameHeight, m_texFrameWidth, m_texFrameHeight }, m_alpha);
    
    DrawImpl();
}

void EnemyBase::Update(float dt)
{
    if (m_state == State::Dying)
    {
        Death(dt);
        return;
    }

    UpdateImpl(dt);
    Move(dt);
    UpdateMatrix();
}

void EnemyBase::Move(float dt)
{
    // 回転移動
    /*m_velocity.x = cos(DirectX::XMConvertToRadians(m_spinAngle)) * 300;
  m_velocity.y = sin(DirectX::XMConvertToRadians(m_spinAngle)) * 300;*/

    m_pos += m_velocity * dt;

    // 画面外チェック
    if (m_pos.x > SCENE.screenWidth + kDeleteMargin || m_pos.y > SCENE.screenHeight + kDeleteMargin ||
        m_pos.x < -SCENE.screenWidth - kDeleteMargin || m_pos.y < -SCENE.screenHeight - kDeleteMargin)
    {
        m_state = State::Dead;
    }
}

void EnemyBase::ShotStraight()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(-m_bulletOffset, 0);
    BULLETMANAGER.CreateBullet(BulletOwner::Enemy, BulletType::Normal, spawnPos, Math::Vector2(-m_bulletSpeed, 0), m_bulletScale, m_bulletColor);
}

void EnemyBase::ShotNWay(int num)
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(-m_bulletOffset, 0);

    float angleStep = 360.0f / num;
    for (int i = 0; i < num; i++)
    {
        float angle = angleStep * i;
        Math::Vector2 velocity =
        {
            cos(DirectX::XMConvertToRadians(angle)) * m_bulletSpeed,
            sin(DirectX::XMConvertToRadians(angle)) * m_bulletSpeed
        };

        BULLETMANAGER.CreateBullet(BulletOwner::Enemy, BulletType::Normal, spawnPos, velocity, m_bulletScale, m_bulletColor);
    }
}

void EnemyBase::ShotAimed()
{
    Math::Vector2 spawnPos = m_pos + Math::Vector2(-m_bulletOffset, 0);

    float deg = GetAngleDeg(m_pos, PLAYERMANAGER.GetPlayer()->GetPos());
    Math::Vector2 velocity =
    {
        cos(DirectX::XMConvertToRadians(deg)) * m_bulletSpeed,
        sin(DirectX::XMConvertToRadians(deg)) * m_bulletSpeed
    };
    BULLETMANAGER.CreateBullet(BulletOwner::Enemy, BulletType::Normal, spawnPos, velocity, m_bulletScale, m_bulletColor);
}

void EnemyBase::ShotRotate(float dt)
{
    m_bulletAngle += m_bulletAngleSpeed * dt;
    if (m_bulletAngle > 360)
    {
        m_bulletAngle -= 360;
    }

    Math::Vector2 dir = {
        cos(DirectX::XMConvertToRadians(m_bulletAngle)),
        sin(DirectX::XMConvertToRadians(m_bulletAngle)) };

    Math::Vector2 spawnPos = m_pos + dir * m_bulletOffset;
    Math::Vector2 bulletSpeed = dir * m_bulletSpeed;

    BULLETMANAGER.CreateBullet(BulletOwner::Enemy, BulletType::Normal, spawnPos, bulletSpeed, m_bulletScale, m_bulletColor);

}

float EnemyBase::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
    float rad = atan2(dest.y - src.y, dest.x - src.x);
    float deg = DirectX::XMConvertToDegrees(rad);
    if (deg < 0) deg += 360.0f;
    return deg;
}

void EnemyBase::TakeDamage(float damage)
{
    Character::TakeDamage(damage);
    TIMEMANAGER.HitStop(kHitStopFrames);
    if (m_hp <= 0)
    {
        m_state = State::Dying;
        SCOREMANAGER.AddScore(m_score);
    }
}
