#pragma once
#include "Application/GameObject/GameObject.h"

class Character : public GameObject
{
public:

    Character() = default;
    Character(Math::Vector2 pos, float scale);
    virtual ~Character() {};

    virtual void TakeDamage(float damage);

protected:

    // HPÅEèÛë‘
    int   m_hp;
    float m_invincibleTimer;
};