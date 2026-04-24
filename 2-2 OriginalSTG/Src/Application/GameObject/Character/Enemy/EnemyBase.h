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

    // 次弾発射までの残り時間
    float m_shotTimer;

    // 画像サイズ
    int m_texFrameSize = 64;

    // 画面外削除の余白距離
    static constexpr float kDeleteMargin = 500.0f;

    // ヒット時
    static constexpr float kHitStopFrames = 0.05f;
};