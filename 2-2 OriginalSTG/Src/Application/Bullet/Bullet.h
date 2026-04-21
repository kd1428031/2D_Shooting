#pragma once

class Bullet
{
public:

    Bullet(Math::Vector2 pos, Math::Vector2 velocity, float scale = 1.0f, Math::Color color= { 1,1,1,1 });
    ~Bullet() {}

    void Init();
    void Update(float dt);
    void Draw();

    void Destroy();

    bool IsAlive() const { return m_isAlive; }

    float GetRadius() const { return kRadius; }
    Math::Vector2 GetPos() const { return m_pos; }
    int GetDamage() { return m_damage; }

private:

    // 座標・移動
    Math::Vector2 m_pos;
    Math::Vector2 m_velocity;

    // サイズ
    float m_scale = 1.0f;

    // 状態
    bool  m_isAlive = true;
    float m_invincibleTimer = 0.0f;

    int m_damage = 1;

    // テクスチャ
    KdTexture *m_tex;

    // 行列
    Math::Matrix m_scaleMat;
    Math::Matrix m_transMat;
    Math::Matrix m_mat;

    Math::Color m_color = { 1,1,1,1 };

    // 定数
    static constexpr float kRadius = 32.0f;
    static constexpr float kDeleteMargin = 500.0f;
    static constexpr int kTexFrameSize = 32;
    static constexpr int kTexOffsetY = kTexFrameSize * 8;
};