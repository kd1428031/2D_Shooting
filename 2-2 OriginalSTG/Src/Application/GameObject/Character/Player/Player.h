#pragma once
#include "Application/GameObject/Character/Character.h"

enum class ShotType
{
    NormalShot,
    PenetratShot
};

class Player : public Character
{
public:

    // 状態管理用
    enum class State
    {
        Alive,      // 生存
        Invincible, // 無敵時間
        Dying,      // 死亡演出
        Dead        // 死亡
    };

    Player() = default;
    ~Player() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void Move(float dt);
    void UpdateAnim(float dt);
    void UpdateInvincible(float dt);

    void Shot(float dt);
    void NormalShot();
    void PenetratShot();

    void TakeDamage(float damage)override;
    void Death(float dt);

    float GetRadius() const { return kRadius; }
    float GetSpeed() const { return m_speed; }
    bool IsAlive() const override{ return m_state != State::Dead; }
    bool IsInvincible() const { return m_state == State::Invincible; }

private:
    
    State m_state;

    float m_speed;

    float m_animSpeed = kAnimSpeed;
    static constexpr float kBlinkInterval = 3.0f;  // まばたき間隔
    float m_blinkTimer = kBlinkInterval;

    // 弾
    ShotType m_shotType;
    bool     m_isShooting;
    float    m_shotTimer;

    // 定数
    // 初期値
    static constexpr float kInitPosX = -500.0f;
    static constexpr float kInitPosY = 0.0f;
    static constexpr float kInitSpeed = 400.0f;
    static constexpr int   kInitHp = 3;

    // 速度
    static constexpr float kLowSpeed = 200;
    static constexpr float kHighSpeed = 600;

    // 当たり判定
    static constexpr float kRadius = 32.0f;

    // 状態
    static constexpr float kInvincibleTime = 2.0f;

    // アニメーション
    static constexpr int   kMaxAnimFrame = 4;
    static constexpr float kAnimSpeed = 7.5f;
    static constexpr int   kTexFrameSize = 81;

    // 弾
    static constexpr float kShotInterval = 0.05f;               // 発射間隔
    static constexpr float kBulletOffsetX = 30.0f;              // 発射位置
    static constexpr float kBulletSpeed = 1300.0f;              // 速さ
    static constexpr float kBulletScale = 2.0f;                 // サイズ
    const Math::Color kBulletColor = {0.0f,1.0f,0.0f,1.0f};     // 色
};