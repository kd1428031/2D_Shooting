#pragma once
#include "Application/GameObject/Character/Character.h"

class EffectBase;

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

    enum class ShotType
    {
        NormalShot,
        PenetratShot
    };

    enum class BombType
    {
        Lightning
    };

    Player() = default;
    ~Player() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void DrawUi();
    void Move(float dt);
    void UpdateAnim(float dt);
    void UpdateInvincible(float dt);

    void Shot(float dt);
    void NormalShot();
    void PenetratShot();

    void Bomb(float dt);
    void RavenBomb(float dt);
    void Lightning();

    void TakeDamage(float damage)override;
    void Death(float dt);

    void SetMp(float mp) { m_mp = mp; }
    void SetActionFlg(bool actionFlg) { m_actionFlg = actionFlg; }
    void SetGameoverFlg(bool gameoverFlg) { m_gameoverFlg = gameoverFlg; }

    float GetRadius() const { return kRadius; }
    float GetSpeed() const { return m_speed; }
    float GetMp() const { return m_mp; }
    int GetBomdWait() { return m_bomdTimer; }
    int GetRavenBomdWait() { return m_ravenBomdTimer; }
    bool GetActionFlg() const { return m_actionFlg; }

    bool IsAlive() const override{ return m_state != State::Dead; }
    bool IsInvincible() const { return m_state == State::Invincible; }
    bool IsIsHit() const { return m_isHit; }

private:
    
    bool m_isHit = false;
    bool m_gameoverFlg = false;

    bool m_lowFlg;

    float m_shotSoundTimer;
    static constexpr float kShotSoundInterval = 0.5f;

    // 定数
    // 初期値
    static constexpr float kInitPosX = -500.0f;
    static constexpr float kInitPosY = 0.0f;
    static constexpr float kInitSpeed = 400.0f;
    static constexpr int   kInitHp = 3;
    static constexpr int   kInitMp = 100;

    // 速度
    static constexpr float kLowSpeed = 10;
    static constexpr float kHighSpeed = 600;

    // 当たり判定
    static constexpr float kRadius = 24.0f;
    static constexpr float kScale = 0.75f;

    // ヒット時
    static constexpr float kHitStopFrames = 3.0f;

    // 状態
    static constexpr float kInvincibleTime = 2.0f;

    // アニメーション
    static constexpr int    kMaxAnimFrame = 4;
    static constexpr float  kAnimSpeed = 7.5f;
    static constexpr int    kTexFrameWidth = 81;
    static constexpr int    kTexFrameHeight = 81;

    // 弾
    static constexpr float kShotInterval = 0.05f;               // 発射間隔
    static constexpr float kBulletOffsetX = 30.0f;              // 発射位置
    static constexpr float kBulletSpeed = 1300.0f;              // 速さ
    static constexpr float kBulletScale = 2.0f;                 // サイズ
    const Math::Color kBulletColor = {0.8f,0.3f,0.8f,1.0f};     // 色

    static constexpr int kBomdInterval = 99;
    static constexpr int kRavenBomdInterval = 50;

    // 状態・ステータス
    float m_mp;
    float m_mpRegen;
    State m_state;
    float m_speed;
    bool m_actionFlg;
    KdTexture *m_heartTex;
    Math::Matrix m_heartMat;
    float m_uiAlpha;

    BombType m_bombType;
    bool     m_isBomd;
    float    m_bomdTimer;

    float    m_ravenBomdTimer;
    bool     m_isRavenBomd;

    // アニメ
    float m_animSpeed = kAnimSpeed;
    static constexpr float kBlinkInterval = 3.0f;  // まばたき間隔
    float m_blinkTimer = kBlinkInterval;

    // 弾
    ShotType m_shotType;
    bool     m_isShooting;
    float    m_shotTimer;

    KdTexture* m_cntTex;
    Math::Matrix m_cntMat;

    int m_uiAlphaBlink = -1;

    EffectBase* m_magicCircle = nullptr;
};