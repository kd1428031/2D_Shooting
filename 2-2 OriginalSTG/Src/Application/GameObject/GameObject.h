#pragma once

class GameObject
{
public:

	GameObject() = default;
    GameObject(Math::Vector2 pos, float scale);
    virtual ~GameObject() = default;

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    void UpdateMatrix();

    virtual bool IsAlive() const { return true; };

    Math::Vector2 GetPos() const { return m_pos; }

protected:

    // 座標・移動
    Math::Vector2 m_pos;
    Math::Vector2 m_velocity;

    // サイズ
    float m_scale = 1.0f;
    float m_angle;
    float m_radius;

    // 色・透明度
    float m_alpha;
    Math::Color m_color = { 1,1,1,1 };

    // アニメーション（x:横フレーム, y:縦フレーム）
    Math::Vector2 m_animFrame;

    // テクスチャ
    KdTexture* m_tex;

    // 行列
    Math::Matrix m_mat;
};