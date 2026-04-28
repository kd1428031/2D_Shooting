#pragma once
#include "Application/GameObject/Character/Character.h"

class EnemyBase : public Character
{
public:

    // 状態管理用
    enum class State
    {
        Alive,  // 生存
        Dying,  // 死亡演出
        Dead    // 死亡
    };

    EnemyBase(Math::Vector2 pos, float scale);
    virtual ~EnemyBase() = default;

    virtual void Init() = 0;
    void Update(float dt)override;
    void Draw() override;
    void Move(float dt);

    // 敵ごとの固有行動（移動パターン・射撃など）
    virtual void UpdateImpl(float dt) = 0;

    // 敵ごとの追加描画処理
    virtual void DrawImpl() {}

    void ShotStraight();        // 直線弾 
    void ShotNWay(int num);     // Way弾 
    void ShotAimed();           // 自機狙い弾 
    void ShotRotate(float dt);  // 回転弾

    float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest);

    // 死亡時の演出処理（エフェクト・アニメーションなど）
    virtual void Death(float dt) = 0;

    void TakeDamage(float damage)override;

    float GetRadius() const { return m_radius; }

    void Destroy(){ m_state = State::Dead; }
    bool IsAlive() const override{ return m_state != State::Dead; };

protected:

    State m_state;
    
    // 撃破時獲得スコア
    int   m_score;

    // 弾
    float       m_shotTimer;
    float       m_shotInterval;
    float       m_bulletOffset;
    float       m_bulletSpeed;
    float       m_bulletScale;
    Math::Color m_bulletColor;
    float       m_bulletAngle;
    float       m_bulletAngleSpeed;

    // 画像サイズ
    int m_texFrameWidth = 64;
    int m_texFrameHeight = 64;

    // 画面外削除の余白距離
    static constexpr float kDeleteMargin = 500.0f;

    // ヒット時
    static constexpr float kHitStopFrames = 0.05f;
};