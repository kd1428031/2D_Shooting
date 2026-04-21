#pragma once
#include "Application/Character/Enemy/EnemyBase.h"

class Enemy : public EnemyBase
{
public:

    Enemy(Math::Vector2 pos, float scale);
    ~Enemy() = default;

    void Init() override;

    void UpdateImpl(float dt)override;
    void Death(float dt)override;

private:

};