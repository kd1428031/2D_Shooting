#pragma once
#include "Application/Character/Character.h"

enum class ShotType
{
    NormalShot
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
    void UpdateMatrix();
    void UpdateAnim(float dt);
    void UpdateInvincible(float dt);

    void Shot(float dt);
    void NormalShot();

    void TakeDamage(float damage)override;
    void Death(float dt);

    float GetRadius() const { return kRadius; }
    bool IsAlive() const { return m_state != State::Dead; }
    bool IsInvincible() const { return m_state == State::Invincible; }

private:
    
    State m_state;

    // 弾
    ShotType m_shotType;
    bool     m_isShooting;
    float    m_shotTimer;

    // 定数：初期値
    static constexpr float kInitPosX = -500.0f;
    static constexpr float kInitPosY = 0.0f;
    static constexpr float kInitSpeed = 800.0f;
    static constexpr int   kInitHp = 3;

    // 定数：当たり判定
    static constexpr float kRadius = 32.0f;

    // 定数：状態
    static constexpr float kInvincibleTime = 2.0f;

    // 定数：アニメーション
    static constexpr int   kMaxAnimFrame = 4;
    static constexpr float kAnimSpeed = 15.0f;
    static constexpr int   kTexFrameSize = 64;

    // 定数：弾
    static constexpr float kShotInterval = 0.05f;   // 発射間隔
    static constexpr float kBulletOffsetX = 30.0f;  // 発射位置
    static constexpr float kBulletSpeed = 750.0f;   // 速さ
    static constexpr float kBulletScale = 2.0f;     // サイズ
};