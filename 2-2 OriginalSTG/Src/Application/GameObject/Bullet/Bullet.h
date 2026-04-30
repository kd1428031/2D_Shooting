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
    Player,  // é©ã@íe
    Enemy    // ìGíe
};

class EnemyBase;

class Bullet : public GameObject
{
public:

    Bullet(BulletOwner owner, BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color= { 1,1,1,1 });
    ~Bullet()override;

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

    // ÇªÇÃìGÇÕÉqÉbÉgçœÇ©Ç«Ç§Ç©
    bool IsAlreadyHit(EnemyBase* enemy) const;

    // ìGÇÉqÉbÉgçœÉäÉXÉgÇ…í«â¡
    void AddHitEnemy(EnemyBase* enemy);

private:

    void InitNormalBullet();
    void InitPenetratBullet();
    void InitRotateBullet();

    BulletOwner m_owner;
    BulletType  m_type;

    // ÉqÉbÉgçœÇ›ìGÉäÉXÉg
    std::vector<EnemyBase*> m_hitEnemies; 

    // èÛë‘
    bool    m_isAlive;
    float   m_lifeTimer;
    int     m_damage;
    float   m_spinAngle;

    int   m_texOffsetY;

    // íËêî
    static constexpr float  kRadius              = 32.0f;
    static constexpr float  kDeleteMargin        = 500.0f;
    static constexpr int    kTexFrameWidth       = 32;
    static constexpr int    kTexFrameHeight      = 32;
    static constexpr int    kTexNormalOffsetY    = kTexFrameWidth * 8;
    static constexpr int    kPenetrateTexOffsetY = 0;
    static constexpr float  kLifeTimer           = 10.0f;
    static constexpr float  kNormalDamage        = 1.0f;
    static constexpr float  kPenetrateDamage     = 0.2f;
    static constexpr float  kRotateSpeed         = 300.0f;
    static constexpr float  kSpinAngleSpeed      = 300.0f;
};