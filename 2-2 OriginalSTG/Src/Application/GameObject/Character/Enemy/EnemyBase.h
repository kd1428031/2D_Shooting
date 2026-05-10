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

    enum class ShotType
    {
        Straight,
        NWay,
        AllRange,
        Aimed,
        Rotate
    };

    enum class EnemyTag
    {
        Normal,
        Boss,
        Summoned
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
    virtual void PreUpdate(float dt);

    virtual void Shot(float dt);

    void ShotStraight();        // 直線弾 
    void ShotNWay();     // Way弾 
    void ShotAllRange();     // Way弾 
    void ShotAimed();           // 自機狙い弾 
    void ShotRotate(float dt);  // 回転弾

    float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest);

    // 死亡時の演出処理（エフェクト・アニメーションなど）
    virtual void PreDeath(){}
    virtual void Death(float dt) = 0;

    virtual void OnHit(){}

    void TakeDamage(float damage)override;

    void SetShotFlg(bool shotFlg) { m_shotFlg = shotFlg; }
    void SetShotType(ShotType shotType) { m_shotType = shotType; }
    void SetState(State state) { m_state = state; }

    EnemyTag GetEnemyTag() const { return m_enemyTag; }
    float GetRadius() const { return m_radius; }

    void Destroy(){ m_state = State::Dead; }
    bool IsAlive() const override{ return m_state != State::Dead; };
    bool IsActive() const { return m_state == State::Alive; }

protected:

    State m_state;
    ShotType m_shotType;
    EnemyTag m_enemyTag = EnemyTag::Normal;
    
    bool m_shotFlg;

    int m_shotNWay;
    int m_shotAllNWay;

    bool m_preUpdateFlg;

    // 撃破時獲得スコア
    int   m_score;

    // 弾
    float       m_shotInterval;
    float       m_shotTimer;
    float       m_bulletOffset;
    float       m_bulletSpeed;
    float       m_bulletScale;
    Math::Color m_bulletColor;
    float       m_bulletAngle;
    float       m_bulletAngleSpeed;
    float       m_baseAngle = 180.0f; // デフォルト左向き
    float       m_spreadAngle = 60.0f; // 扇の広がり角

    // 画像サイズ
    int m_texFrameWidth = 64;
    int m_texFrameHeight = 64;

    // 画面外削除の余白距離
    static constexpr float kDeleteMargin = 500.0f;

    // ヒット時
    static constexpr float kHitStopFrames = 0.05f;
};