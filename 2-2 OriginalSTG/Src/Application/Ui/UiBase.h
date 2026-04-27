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
	virtual void Draw();
	void UpdateMatrix();

	virtual void UpdateImpl(float dt) {};
	virtual void DrawImpl() {};

	bool IsAlive() const { return m_isAlive; }

protected:

	// 座標
	Math::Vector2 m_pos;

	// 状態
	bool m_isAlive;
	
	// サイズ
	float m_scale = 1.0f;
	float m_angle;

	// 色・透明度
	float m_alpha;
	Math::Color m_color = { 1,1,1,1 };

	// アニメーション（x:横フレーム, y:縦フレーム）
	Math::Vector2 m_animFrame;

	// テクスチャ
	KdTexture* m_tex;

	// 画像サイズ
	int m_texFrameSize = 64;

	// 行列
	Math::Matrix m_transMat;
	Math::Matrix m_rotMat;
	Math::Matrix m_scaleMat;
	Math::Matrix m_mat;
};