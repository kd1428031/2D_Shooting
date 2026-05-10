#pragma once
#include "Application/GameObject/Character/Enemy/EnemyBase.h"

class GrimReaper : public EnemyBase
{
public:

    enum class AnimeState
    {
        Idle,
        Summon,
        Death
    };

    GrimReaper(Math::Vector2 pos, float scale);
    ~GrimReaper() = default;

    void Init() override;

    void UpdateImpl(float dt)override;
    void PreUpdate(float dt)override;
    void Shot(float dt)override;

    void PreSummon();
    void Summon(float dt);

    void UpdateSummon(float dt);
    void UpdateShot(float dt);
    void UpdateMove(float dt);
    void UpdataAnim(float dt);

    void OnHit()override;
    void PreDeath()override;
    void Death(float dt)override;

private:

    AnimeState m_animeState = AnimeState::Idle;

    bool m_deathFlg;
    bool m_createFlg;

    // 全方位弾用カウンタ
    float m_allShotTimer;
    static constexpr float kAllShotTimerInterval = 7.5f;

    // 召喚用カウンタ
    float m_summonTimer;
    static constexpr float kSummonTimerInterval = 5.0f;

    // 移動開始用カウンタ
    float m_moveTimer;
    static constexpr float kMoveTimerInterval = 5.0f;

    // 移動中用カウンタ
    float m_movingTimer;
    static constexpr float kMovingTimerInterval = 3.0f;

    bool m_moveFlg;
    static constexpr float kMovingSpeed = 200.0f;

    // 初期化用定数
    static constexpr int    kInitHp = 60;
    const Math::Vector2     kInitVelocity = { 0.0f, 0.0f };

    // 召喚数上限
    static constexpr int kSummonMax = 8;

    // 基本設定用定数
    static constexpr float  kRadius = 50.0f * 2;
    static constexpr int    kTexFrameWidth = 100.0f;
    static constexpr int    kTexFrameHeight = 100.0f;
    static constexpr float  kAnimSpeed = 20.0f;
    static constexpr int    kIdleAnimMax = 4;
    static constexpr int    kDeathAnimMax = 7;
    static constexpr int    kScore = 100;

    // 弾
    static constexpr float  kShotInterval = 0.5f;                    // 発射間隔
    static constexpr float  kBulletOffsetX = 100.0f;                 // 発射位置
    static constexpr float  kBulletSpeed = 200.0f;                   // 速さ
    static constexpr float  kBulletScale = 2.0f;                     // サイズ
    static constexpr float  kBulletAngleSpeed = 600.0f;              // サイズ
    const Math::Color       kBulletColor = { 0.0f,0.0f,0.0f,1.0f };  // 色
};