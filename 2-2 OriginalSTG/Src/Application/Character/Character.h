#pragma once

class Character
{
public:

    Character() = default;
    Character(Math::Vector2 pos, float scale);
    virtual ~Character() {};

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    virtual void TakeDamage(float damage);
    virtual bool IsAlive() const = 0;

    Math::Vector2 GetPos() const { return m_pos; }

protected:

    // 座標・移動
    Math::Vector2 m_pos;
    Math::Vector2 m_velocity;

    // サイズ
    float m_scale = 1.0f;
    float m_angle;
    float m_radius;

    // HP・状態
    int   m_hp;
    float m_invincibleTimer;

    // アニメーション（x:横フレーム, y:縦フレーム）
    Math::Vector2 m_animFrame;

    // テクスチャ
    KdTexture *m_tex;

    // 行列
    Math::Matrix m_transMat;
    Math::Matrix m_rotMat;
    Math::Matrix m_scaleMat;
    Math::Matrix m_mat;
};