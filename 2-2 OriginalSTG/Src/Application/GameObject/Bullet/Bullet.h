#pragma once
#include "Application/GameObject/GameObject.h"

enum class BulletType
{
    Normal,
    Penetrat,
    Rotate
};

enum class BulletOwner
{
    Player,  // ©‹@’e
    Enemy    // “G’e
};

class EnemyBase;

class Bullet : public GameObject
{
public:

    Bullet(BulletOwner owner, BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color= { 1,1,1,1 });
    ~Bullet();

    void Init()             override;
    void Update(float dt)   override;
    void Draw()             override;

    void Move(float dt);
    void UpdateRotate(float dt);
    void Destroy();

    BulletOwner     GetBulletOwner()    const           { return m_owner; }
    float           GetRadius()         const           { return kRadius; }
    float           GetHitRadius()      const           { return kRadius / 4; }
    Math::Vector2   GetPos()            const           { return m_pos; }
    int             GetDamage()         const           { return m_damage; }

    bool IsAlive()                      const override  { return m_isAlive; }
    bool IsPenetrat()                   const           { return m_type == BulletType::Penetrat; }

    // ‚»‚Ì“G‚ÍƒqƒbƒgÏ‚©‚Ç‚¤‚©
    bool IsAlreadyHit(EnemyBase* enemy) const;

    // “G‚ğƒqƒbƒgÏƒŠƒXƒg‚É’Ç‰Á
    void AddHitEnemy(EnemyBase* enemy);

private:

    BulletOwner m_owner;
    BulletType  m_type;

    // ƒqƒbƒgÏ‚İ“GƒŠƒXƒg
    std::vector<EnemyBase*> m_hitEnemies; 

    // ó‘Ô
    bool    m_isAlive;
    float   m_lifeTimer;
    int     m_damage;
    float   m_spinAngle;

    // ’è”
    static constexpr float  kRadius         = 32.0f;
    static constexpr float  kDeleteMargin   = 500.0f;
    static constexpr int    kTexFrameSize   = 32;
    static constexpr int    kTexOffsetY     = kTexFrameSize * 8;
    static constexpr float  kLifeTimer      = 10.0f;
};