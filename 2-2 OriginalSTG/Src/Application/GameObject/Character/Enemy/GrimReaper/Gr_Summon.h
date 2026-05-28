#pragma once
#include "Application/GameObject/Character/Enemy/EnemyBase.h"

class Gr_Summon : public EnemyBase
{
public:

    Gr_Summon(Math::Vector2 pos, float scale);
    ~Gr_Summon() = default;

    void Init() override;

    void UpdateImpl(float dt)override;
    void OnHit()override;
    void PreUpdate(float dt)override;
    void PreDeath()override;
    void Death(float dt)override;

    void SetBasePos(Math::Vector2 basePos) { m_basePos = basePos; }
    void SetOffset(Math::Vector2 offset) { m_offset = offset; }

private:

    static constexpr int    kInitHp = 10;
    const Math::Vector2     kInitVelocity = { 0.0f, 0.0f };

    static constexpr float  kRadius = 24.0f;
    static constexpr int    kTexFrameWidth = 50.0f;
    static constexpr int    kTexFrameHeight = 50.0f;
    static constexpr int    kInitScale = 2.0f;
    static constexpr float  kAnimSpeed = 5.0f;
    static constexpr int    kIdleAnimMax = 4;
    static constexpr int    kDeathAnimMaxX = 3;
    static constexpr int    kDeathAnimMaxY = 1;
    static constexpr int    kScore = 50;

    // 弾
    static constexpr float  kShotInterval = 1.0f;                     // 発射間隔
    static constexpr float  kBulletOffsetX = 20.0f;                    // 発射位置
    static constexpr float  kBulletSpeed = 200.0f;                   // 速さ
    static constexpr float  kBulletScale = 1.0f;                     // サイズ
    static constexpr float  kBulletAngleSpeed = 600.0f;                     // サイズ
    const Math::Color       kBulletColor = { 1.0f,1.0f,1.0f,1.0f };  // 色

    bool m_preAnimFlg;
    bool m_deathFlg;

    Math::Vector2 m_basePos;

    float m_deg;

    Math::Vector2 m_offset;
};