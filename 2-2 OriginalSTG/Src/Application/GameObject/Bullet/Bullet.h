#pragma once
#include "Application/GameObject/GameObject.h"

enum class BulletType
{
    Normal,
    Penetrat
};

class EnemyBase;

class Bullet : public GameObject
{
public:

    Bullet(BulletType type, Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color= { 1,1,1,1 });
    ~Bullet();

    void Init()override;
    void Update(float dt)override;
    void Draw()override;
    void Move(float dt);
    void UpdateMatrix();

    void Destroy();

    float GetRadius() const { return kRadius; }
    Math::Vector2 GetPos() const { return m_pos; }
    int GetDamage() const { return m_damage; }

    bool IsAlive() const override { return m_isAlive; }
    bool IsPenetrat() const { return m_type == BulletType::Penetrat; }

    // その敵はヒット済かどうか
    bool IsAlreadyHit(EnemyBase* enemy) const;

    // 敵をヒット済リストに追加
    void AddHitEnemy(EnemyBase* enemy);

private:

    BulletType m_type;

    // ヒット済み敵リスト
    std::vector<EnemyBase*> m_hitEnemies; 

    // 状態
    bool  m_isAlive = true;
    int m_damage = 1;

    // 定数
    static constexpr float kRadius = 32.0f;
    static constexpr float kDeleteMargin = 500.0f;
    static constexpr int kTexFrameSize = 32;
    static constexpr int kTexOffsetY = kTexFrameSize * 8;
};