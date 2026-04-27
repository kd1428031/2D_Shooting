#pragma once

// 継承の場合のみインクルード許可します！！
#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() {}

	void Init()				override;
	void Update(float dt)	override;
	void Draw()				override;

private:

	KdTexture m_tex;
	KdTexture m_startTex;

	float m_alpha = 1.0f;
	float m_addAlpha = 0.01f;
};