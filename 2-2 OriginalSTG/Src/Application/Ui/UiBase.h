#pragma once

class UiBase
{
public:

	UiBase();
	~UiBase();

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw();
	void UpdateMatrix();

protected:

	// 座標
	Math::Vector2 m_pos;

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