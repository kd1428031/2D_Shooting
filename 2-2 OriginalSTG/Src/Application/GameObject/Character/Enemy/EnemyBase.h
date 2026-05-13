#pragma once
#include "Application/GameObject/Character/Character.h"

class EnemyBase : public Character
{
public:

    // 状態管理用
    enum class State
    {
        Alive,  // 生存
        Invincible,
        Dying,  // 死亡演出
        Dead    // 死亡
    };

    enum class ShotType
    {
        None,
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

    // 死亡時の演出処理（エフェクト・アニメーションなど）
    virtual void PreDeath(){}
    virtual void Death(float dt) = 0;

    virtual void OnHit(){}

    void TakeDamage(float damage)override;

    void SetColor(Math::Color color) { m_color = color; }
    void SetHp(int hp) { m_hp = hp; }
    void SetRadius(float radius) { m_radius = radius; }
    void SetVelocity(Math::Vector2 velocity) { m_velocity = velocity; }
    void SetScale(float scale) { m_scale = scale; }
    void SetShotType(ShotType shotType) { m_shotType = shotType; }
    void SetState(State state) { m_state = state; }
    void SetStopPos(Math::Vector2 stopPos) { m_stopPos = stopPos; }
    void SetBulletSpeed(float bulletSpeed) { m_bulletSpeed = bulletSpeed; }
    void SetShotInterval(float shotInterval) { m_shotInterval = shotInterval; }
    void SetBulletAngleSpeed(float bulletAngleSpeed) { m_bulletAngleSpeed = bulletAngleSpeed; }

    EnemyTag GetEnemyTag() const { return m_enemyTag; }
    float GetRadius() const { return m_radius; }

    void Destroy(){ m_state = State::Dead; }
    bool IsAlive() const override{ return m_state != State::Dead; };
    bool IsActive() const { return m_state == State::Alive; }
    bool IsInvincible() const { return m_state == State::Invincible; }

protected:

    State m_state;
    ShotType m_shotType;
    EnemyTag m_enemyTag = EnemyTag::Normal;
    
    Math::Vector2 m_stopPos = { -4000, 0 };

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
    static constexpr float kDeleteMargin = 200.0f;

    // ヒット時
    static constexpr float kHitStopFrames = 0.05f;
};