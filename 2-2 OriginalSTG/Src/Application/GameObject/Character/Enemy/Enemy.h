#pragma once
#include "Application/GameObject/Character/Enemy/EnemyBase.h"

class Enemy : public EnemyBase
{
public:

    Enemy(Math::Vector2 pos, float scale);
    ~Enemy() = default;

    void Init() override;

    void UpdateImpl(float dt)override;
    void Death(float dt)override;

private:

    static constexpr float kRadius = 32.0f;

    // 弾
    static constexpr float kShotInterval = 0.05f;              // 発射間隔
    static constexpr float kBulletOffsetX = 30.0f;             // 発射位置
    static constexpr float kBulletSpeed = 300.0f;              // 速さ
    static constexpr float kBulletScale = 2.0f;                // サイズ
    const Math::Color kBulletColor = { 0.0f,1.0f,0.0f,1.0f };  // 色
};