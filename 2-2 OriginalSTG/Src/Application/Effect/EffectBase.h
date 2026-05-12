#pragma once

enum class EffectType
{
	Lightning,
	LightningText,
	SoulLinkText,
	MagicCircle
};

class EffectBase
{
public:

	EffectBase(Math::Vector2 pos, float scale);
	virtual ~EffectBase() = default;

	virtual void Init() = 0;
	void Update(float dt);
	virtual void Draw() = 0;
	virtual void DrawBack(){}
	virtual void UpdateMatrix();
	virtual void UpdateImpl(float dt) {};

	Math::Matrix CreateMatrix(Math::Vector2 offset);
	Math::Matrix CreateMatrix(Math::Vector2 pos, Math::Vector2 scale, float angle);

	bool IsAlive() const { return m_isAlive; }
	void Kill();
	virtual void OnExit();
	void SetTargetPos(Math::Vector2 targetPos) { m_targetPos = targetPos; }

	virtual EffectType GetEffectType() const = 0;

protected:

	// 座標
	Math::Vector2 m_pos;

	Math::Vector2 m_targetPos = {};

	// 状態
	bool m_isAlive;
	bool m_isExiting;

	// サイズ
	float m_scale = 1.0f;
	float m_angle;

	Math::Vector2 m_animFrame;

	// 色
	Math::Color m_color = { 1,1,1,1 };

	// テクスチャ
	KdTexture* m_tex;

	// 行列
	Math::Matrix m_mat;
};