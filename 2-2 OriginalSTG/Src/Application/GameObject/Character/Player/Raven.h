#pragma once
#include "Application/GameObject/Character/Character.h"

class Raven : public Character
{
public:

    // 状態管理用
    enum class State
    {
        Alive,      // 生存
        Dying,      // 死亡演出
        Dead        // 死亡
    };


    Raven() = default;
    ~Raven() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;

    void Move(float dt);
    void UpdateAnim(float dt);

    void Shot(float dt);
    void ShotNWay(int num);
    void Death(float dt);

    void SetPowUpFlg(bool powUpFlg) { m_powUpFlg = powUpFlg; }

    bool IsAlive() const override { return m_state != State::Dead; }
    bool GetPowUpFlg() { return m_powUpFlg; }
    float GetPowUpTimer() { return m_powUpTimer; }

private:

    // 定数
    // 初期値
    static constexpr float kInitPosX = -500.0f;
    static constexpr float kInitPosY = 0.0f;
    static constexpr float kInitSpeed = 400.0f;
    static constexpr int   kInitHp = 3;
    static constexpr int   kInitMp = 100;

    // 速度
    static constexpr float kSpeed = 200;

    // 当たり判定
    static constexpr float kRadius = 24.0f;
    static constexpr float kScale = 1.5f;

    // アニメーション
    static constexpr int    kMaxAnimFrameX = 4;
    static constexpr int    kMaxAnimFrameY = 3;
    static constexpr float  kAnimSpeed = 10.0f;
    static constexpr int    kTexFrameWidth = 48;
    static constexpr int    kTexFrameHeight = 48;

    // 弾
    static constexpr float kShotInterval = 0.5f;               // 発射間隔
    static constexpr float kBulletOffsetX = 30.0f;              // 発射位置
    static constexpr float kBulletSpeed = 1300.0f;              // 速さ
    static constexpr float kBulletScale = 2.0f;                 // サイズ
    const Math::Color kBulletColor = { 0.8f,0.3f,0.8f,1.0f };     // 色

    static constexpr int kBomdInterval = 99;

    // 状態・ステータス
    State m_state;
    float m_speed;

    // アニメ
    float m_animSpeed = kAnimSpeed;

    // 弾
    bool     m_isShooting;
    float    m_shotTimer;

    float m_deg;

    float       m_baseAngle = 0.0f; 
    float       m_spreadAngle = 60.0f;

    bool m_powUpFlg;

    float m_powUpTimer;
    static constexpr float kPowUpTimerInterval = 99.0f;
};