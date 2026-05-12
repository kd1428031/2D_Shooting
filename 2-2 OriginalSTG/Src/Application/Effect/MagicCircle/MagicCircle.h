#pragma once
#include "Application/Effect/EffectBase.h"

class MagicCircle : public EffectBase
{
public:

	MagicCircle(Math::Vector2 pos, float scale);
	~MagicCircle() = default;

	void Init();
	void Draw()override{}
	void DrawBack() override;

	void UpdateImpl(float dt)override;
	void UpdateMatrix()override;

	void OnExit()override;

	EffectType GetEffectType() const { return EffectType::MagicCircle; }

private:

	const Math::Color		kInitColor = { 1.0f,1.0f,1.0f,0.75f };
	static constexpr int	kTexFrameWidth = 128;
	static constexpr int	kTexFrameHeight = 128;
	static constexpr float	kInitAngle = 0.0f;

	static constexpr float kAnimSpeed = 100.0f;
	static constexpr int kAnimMaxX = 78.0f;
	static constexpr int kAnimMaxY = 0.0f;

	bool m_upperFlg;
	bool m_onExitFlg;
};