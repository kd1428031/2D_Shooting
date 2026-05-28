#pragma once

class GameObject;

enum class EffectType
{
	Lightning,
	LightningText,
	SoulLinkText,
	MagicCircle,
	HitEffect,
	MpMax
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
	virtual void DrawFront(){}
	virtual void UpdateMatrix();
	virtual void UpdateImpl(float dt) {};

	Math::Matrix CreateMatrix(Math::Vector2 offset);
	Math::Matrix CreateMatrix(Math::Vector2 pos, Math::Vector2 scale, float angle);

	void SetOwner(GameObject* owner) { m_owner = owner; }

	bool IsAlive() const { return m_isAlive; }
	void Kill();
	virtual void OnExit();

	virtual EffectType GetEffectType() const = 0;

protected:

	GameObject *m_owner = nullptr;

	// 座標
	Math::Vector2 m_pos;

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