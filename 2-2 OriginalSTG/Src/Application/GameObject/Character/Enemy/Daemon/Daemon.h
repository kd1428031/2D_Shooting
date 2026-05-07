#pragma once
#include "Application/GameObject/Character/Enemy/EnemyBase.h"

class Daemon : public EnemyBase
{
public:

    Daemon(Math::Vector2 pos, float scale);
    ~Daemon() = default;

    void Init() override;

    void UpdateImpl(float dt)override;
    void OnHit()override;
    void PreDeath()override;
    void Death(float dt)override;

private:

    static constexpr int    kInitHp = 30;
    const Math::Vector2     kInitVelocity = { -30.0f, 0.0f };

    static constexpr float  kRadius = 32.0f;
    static constexpr int    kTexFrameWidth = 81.0f;
    static constexpr int    kTexFrameHeight = 71.0f;
    static constexpr float  kAnimSpeed = 20.0f;
    static constexpr int    kIdleAnimMax = 4;
    static constexpr int    kDeathAnimMax = 7;
    static constexpr int    kScore = 100;

    // 弾
    static constexpr float  kShotInterval = 0.1f;                     // 発射間隔
    static constexpr float  kBulletOffsetX = 30.0f;                    // 発射位置
    static constexpr float  kBulletSpeed = 300.0f;                   // 速さ
    static constexpr float  kBulletScale = 2.0f;                     // サイズ
    static constexpr float  kBulletAngleSpeed = 600.0f;                     // サイズ
    const Math::Color       kBulletColor = { 1.0f,0.2f,0.2f,1.0f };  // 色
};