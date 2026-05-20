#pragma once
#include "Application/GameObject/GameObject.h"

class Player;

class ItemBase : public GameObject
{
public:
    
    ItemBase(Math::Vector2 pos, float scale = 1.0f);
    virtual ~ItemBase()override;

    virtual void Init() = 0;
    void Update(float dt)   override;
    void Draw()             override;

    virtual void UpdateImpl(float dt){}

    virtual void OnHit(Player* player) = 0;

    void Destroy();

    float           GetRadius()         const { return m_radius; }
    Math::Vector2   GetPos()            const { return m_pos; }

    bool IsAlive()                      const override { return m_isAlive; }

protected:

    // 状態
    bool    m_isAlive;
    float   m_lifeTimer;

    // 画像サイズ
    int m_texFrameWidth = 64;
    int m_texFrameHeight = 64;

    // 定数
    static constexpr float  kDeleteMargin = 500.0f;
    static constexpr float  kLifeTimer = 10.0f;
};