#pragma once

enum class UiType
{
	TitleName,
	Score,
	WarningCutIn
};

class UiBase
{
public:

	UiBase();
	virtual ~UiBase() = default;

	virtual void Init() = 0;
	void Update(float dt);
	virtual void Draw() = 0;
	void UpdateMatrix();
	virtual void UpdateImpl(float dt) {};

	Math::Matrix CreateMatrix(Math::Vector2 offset);

	bool IsAlive() const { return m_isAlive; }
	void Kill();
	virtual void OnExit();

	virtual UiType GetUiType() const = 0;

protected:

	// 座標
	Math::Vector2 m_pos;

	// 状態
	bool m_isAlive;
	bool m_isExiting;

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