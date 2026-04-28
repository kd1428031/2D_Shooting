#pragma once

enum class UiType
{
	Score,
};

class UiBase
{
public:

	UiBase();
	virtual ~UiBase() = default;

	virtual void Init() = 0;
	virtual void Update(float dt);
	virtual void Draw() = 0;
	void UpdateMatrix();

	virtual void UpdateImpl(float dt) {};

	bool IsAlive() const { return m_isAlive; }

protected:

	// 座標
	Math::Vector2 m_pos;

	// 状態
	bool m_isAlive;
	
	// サイズ
	float m_scale = 1.0f;
	float m_angle;

	// 色
	Math::Color m_color = { 1,1,1,1 };

	// テクスチャ
	KdTexture* m_tex;

	// 行列
	Math::Matrix m_mat;
};