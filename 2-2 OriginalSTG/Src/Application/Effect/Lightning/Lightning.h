#pragma once
#include "Application/Effect/EffectBase.h"

class Lightning : public EffectBase
{
public:

	Lightning(Math::Vector2 pos, float scale);
	~Lightning() = default;

	void Init();
	void Draw() override{}
	void DrawFront()override;
	void UpdateImpl(float dt)override;

	EffectType GetEffectType() const { return EffectType::Lightning; }

private:

	Math::Vector2 m_velocity;

	const Math::Color		kInitColor = { 1.0f,1.0f,1.0f,1.0f };
	const Math::Vector2		kInitVelocity = { 0.0f, -20.0f };
	static constexpr int	kTexFrameWidth = 128;
	static constexpr int	kTexFrameHeight = 128;
	static constexpr float	kInitAngle = 0.0f;

	static constexpr float kAnimSpeed = 1.5f;
	static constexpr int kAnimMaxX = 5.0f;
	static constexpr int kAnimMaxY = 11.0f;

	float m_timer;
};