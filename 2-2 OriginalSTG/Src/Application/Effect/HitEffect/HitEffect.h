#pragma once
#include "Application/Effect/EffectBase.h"

class HitEffect : public EffectBase
{
public:

	HitEffect(Math::Vector2 pos, float scale);
	~HitEffect() = default;

	void Init();
	void Draw() override {}
	void DrawFront()override;
	void UpdateImpl(float dt)override;

	EffectType GetEffectType() const { return EffectType::HitEffect; }

private:

	Math::Vector2 m_velocity;

	const Math::Color		kInitColor = { 1.0f,0.0f,0.0f,1.0f };
	static constexpr int	kTexFrameWidth = 1024;
	static constexpr int	kTexFrameHeight = 1024;
	static constexpr float	kInitAngle = 0.0f;

	static constexpr float kAnimSpeed = 25.0f;
	static constexpr int kAnimMaxX = 16;

	float m_timer;
};